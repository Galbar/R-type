#include "GamePlugin.hpp"
#include "Defines.hpp"
#include <algorithm>
#include "GameBehavior.hpp"
#include "Resources.hpp"
#include "tiled/extensions/lua.hpp"
extern "C"
{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>

    void error (lua_State *L, const char *fmt, ...) {
        va_list argp;
        va_start(argp, fmt);
        vfprintf(stderr, fmt,  argp);
        va_end(argp);
        lua_close(L);
        exit(EXIT_FAILURE);
    }
}

GamePlugin::GamePlugin():
p_scene(new Scene),
p_inactive_actors(new std::unordered_set<h2d::Actor*>),
p_player_collider(new std::unordered_set<Collider*>),
p_enemy_collider(new std::unordered_set<Collider*>),
p_player_bullet_collider(new std::unordered_set<Collider*>),
p_enemy_bullet_collider(new std::unordered_set<Collider*>),
p_wall_collider(new std::unordered_set<Collider*>)
{

}

GamePlugin::~GamePlugin()
{
    delete p_scene;
    delete p_wall_collider;
    delete p_enemy_bullet_collider;
    delete p_player_bullet_collider;
    delete p_enemy_collider;
    delete p_player_collider;
    delete p_inactive_actors;
}

void GamePlugin::gameStart()
{
    p_camera_kinematic = game().makeActor()->addBehavior<h2d::Kinematic>();
    p_mogl = game().getPlugin<mogl::MultimediaOGL>();

    loadResources(*p_mogl, "./res/resources.def");
}

void GamePlugin::gameEnd()
{
}

void GamePlugin::preFixedUpdate()
{
    sf::FloatRect intersection;
    for (Collider* player_col : *p_player_collider)
    {
        player_col->clearCollisions();
        for (Collider* enemy_col : *p_enemy_collider)
        {
            enemy_col->clearCollisions();
            if (player_col->getRect().intersects(enemy_col->getRect(), intersection))
            {
                Collision col { enemy_col, intersection };
                player_col->pushCollision(col);
                col.other = player_col;
                enemy_col->pushCollision(col);
            }
        }

        for (Collider* enemy_bullet_col : *p_enemy_bullet_collider)
        {
            enemy_bullet_col->clearCollisions();
            if (player_col->getRect().intersects(enemy_bullet_col->getRect(), intersection))
            {
                Collision col { enemy_bullet_col, intersection };
                player_col->pushCollision(col);
                col.other = player_col;
                enemy_bullet_col->pushCollision(col);
            }
        }

        for (Collider* wall : *p_wall_collider)
        {
            wall->clearCollisions();
            if (player_col->getRect().intersects(wall->getRect(), intersection))
            {
                Collision col { wall, intersection };
                player_col->pushCollision(col);
                col.other = player_col;
                wall->pushCollision(col);
            }
        }
    }

    for (Collider* enemy_col : *p_enemy_collider)
    {
        for (Collider* wall : *p_wall_collider)
        {
            if (enemy_col->getRect().intersects(wall->getRect(), intersection))
            {
                Collision col { wall, intersection };
                enemy_col->pushCollision(col);
                col.other = enemy_col;
                wall->pushCollision(col);
            }
        }

        for (Collider* player_bullet_col : *p_player_bullet_collider)
        {
            if (enemy_col->getRect().intersects(player_bullet_col->getRect(), intersection))
            {
                Collision col { player_bullet_col, intersection };
                enemy_col->pushCollision(col);
                col.other = enemy_col;
                player_bullet_col->pushCollision(col);
            }
        }
    }

    for (Collider* enemy_bullet_col : *p_enemy_bullet_collider)
    {
        for (Collider* wall : *p_wall_collider)
        {
            if (enemy_bullet_col->getRect().intersects(wall->getRect(), intersection))
            {
                Collision col { wall, intersection };
                enemy_bullet_col->pushCollision(col);
                col.other = enemy_bullet_col;
                wall->pushCollision(col);
            }
        }

        for (Collider* player_bullet_col : *p_player_bullet_collider)
        {
            player_bullet_col->clearCollisions();
            if (enemy_bullet_col->getRect().intersects(player_bullet_col->getRect(), intersection))
            {
                Collision col { player_bullet_col, intersection };
                enemy_bullet_col->pushCollision(col);
                col.other = enemy_bullet_col;
                player_bullet_col->pushCollision(col);
            }
        }
    }
}

void GamePlugin::postFixedUpdate()
{
    if (p_change_level)
    {
        p_change_level = false;

        //Clear resources from previous scene
        for (auto name : p_scene->animations)
        {
            p_mogl->spriteAnimations().free(name);
        }
        for (auto name : p_scene->textures)
        {
            p_mogl->textures().free(name);
        }
        for (auto actor : p_scene->actors)
        {
            game().destroy(actor);
        }

        // Init new scene
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        if (luaL_loadfile(L, ("res/levels/" + p_next_level_name + ".lua").c_str()) || lua_pcall(L, 0, 1, 0))
        {
            error(L, "cannot load map: %s",
                     lua_tostring(L, -1));
            return;
        }
        p_active_map = tiled::Map();
        tiled::lua::load(p_active_map, L);
        lua_close(L);

        tiled::Color c = p_active_map.getBackgroundColor();
        p_mogl->setClearColor(sf::Color(c.r, c.g, c.b));

        int z_index = p_active_map.getLayers().size();
        for (tiled::Layer* layer : p_active_map.getLayers())
        {
            if (!layer->getVisibility()) continue;
            if (layer->getType() == tiled::Layer::LayerType::TILE_LAYER)
            {
                h2d::Actor* layer_actor = game().makeActor();
                p_scene->actors.push_back(layer_actor);
                layer_actor->transform().z = z_index;
                tiled::TileLayer* tile_layer = static_cast<tiled::TileLayer*>(layer);
                int i = -1;
                for (int gid : tile_layer->getTileMap())
                {
                    ++i;
                    if (gid == 0) continue;
                    int ts_idx = p_active_map.findTilesetIndex(gid);
                    tiled::Tileset* ts = p_active_map.getTilesets()[ts_idx];
                    int tile_id = gid - ts->getGId();
                    int x = i % tile_layer->getWidth();
                    int y = i / tile_layer->getWidth();
                    std::size_t found = ts->getImage()->getSource().find_last_of("/\\");
                    std::string filename = ts->getImage()->getSource().substr(found+1);
                    sf::Texture* tex = p_mogl->textures().get(filename);
                    if (tex == nullptr)
                    {
                        p_mogl->textures().load(filename, "res/levels/" + ts->getImage()->getSource());
                        tex = p_mogl->textures().get(filename);
                        p_scene->textures.push_back(filename);
                    }
                    mogl::Drawable* drawable;
                    auto it = ts->getTiles().find(tile_id);
                    if (it == ts->getTiles().end())
                    {
                        int ts_width = (tex->getSize().x - ts->getMargin()) / ts->getTileWidth();
                        sf::IntRect texrect(
                                ts->getMargin() + (ts->getSpacing() + ts->getTileWidth()) * (tile_id % ts_width),
                                ts->getMargin() + (ts->getSpacing() + ts->getTileHeight()) * (tile_id / ts_width),
                                ts->getTileWidth(),
                                ts->getTileHeight());
                        drawable = layer_actor->addBehavior<mogl::Sprite>(
                                static_cast<float>(ts->getTileWidth()) / TILE_SIZE,
                                static_cast<float>(ts->getTileHeight()) / TILE_SIZE,
                                tex, texrect);
                    }
                    else
                    {
                        tiled::Tile* tile = it->second;
                        std::string animation_name = "tile_" + std::to_string(tile->getGId());
                        mogl::SpriteAnimation* anim = p_mogl->spriteAnimations().get(animation_name);
                        if (anim == nullptr)
                        {
                            std::vector<unsigned int> frame_order;
                            std::vector<h2d::Time> frame_time;
                            for (auto frame : tile->getAnimation())
                            {
                                frame_order.push_back(frame.tile_id);
                                frame_time.push_back(h2d::Time::milliseconds(frame.duration));
                            }
                            mogl::SpriteAnimation anim_data {
                                tex,
                                ts->getMargin(), ts->getMargin(), ts->getSpacing(), ts->getSpacing(), ts->getTileWidth(), ts->getTileHeight(),
                                frame_order,
                                frame_time
                            };

                            p_mogl->spriteAnimations().load(animation_name, anim_data);
                            p_scene->animations.push_back(animation_name);
                            anim = p_mogl->spriteAnimations().get(animation_name);
                        }

                        drawable = layer_actor->addBehavior<mogl::AnimatedSprite>(
                                static_cast<float>(ts->getTileWidth()) / TILE_SIZE,
                                static_cast<float>(ts->getTileHeight()) / TILE_SIZE,
                                anim);
                    }
                    drawable->transform().x = static_cast<float>(x * p_active_map.getTileWidth())/ TILE_SIZE;
                    drawable->transform().y = static_cast<float>(y * p_active_map.getTileHeight()) / TILE_SIZE;;
                }
            }
            else if (layer->getType() == tiled::Layer::LayerType::OBJECT_LAYER)
            {
                auto object_layer = static_cast<tiled::ObjectLayer*>(layer);

                for (auto object : object_layer->getObjects())
                {
                    auto actor = game().makeActor();
                    actor->transform().z = z_index;
                    actor->transform().x = static_cast<float>(object->getX()) / TILE_SIZE;
                    actor->transform().y = static_cast<float>(object->getY()) / TILE_SIZE;
                    p_factory->build(object->getType(), *actor, *object);
                    addActor(actor);
                }
            }
            else if (layer->getType() == tiled::Layer::LayerType::IMAGE_LAYER)
            {
                auto image_layer = static_cast<tiled::ImageLayer*>(layer);

                std::size_t found = image_layer->getImage()->getSource().find_last_of("/\\");
                std::string filename = image_layer->getImage()->getSource().substr(found+1);
                sf::Texture* tex = p_mogl->textures().get(filename);
                if (tex == nullptr)
                {
                    p_mogl->textures().load(filename, "res/levels/" + image_layer->getImage()->getSource());
                    tex = p_mogl->textures().get(filename);
                    p_scene->textures.push_back(filename);
                }
                auto layer_actor = game().makeActor();
                layer_actor->addBehavior<mogl::Sprite>(
                        static_cast<float>(tex->getSize().x) / TILE_SIZE,
                        static_cast<float>(tex->getSize().y) / TILE_SIZE,
                        p_mogl->textures().get(filename)
                        );
                p_scene->actors.push_back(layer_actor);
                layer_actor->transform().z = z_index;

                layer_actor->transform().x = static_cast<float>(image_layer->getX()) / TILE_SIZE;
                layer_actor->transform().y = static_cast<float>(image_layer->getY()) / TILE_SIZE;
            }
            else
            {
                h2d_log("Layer '" << layer->getName() << "'. Type unknown. Ignoring");
            }
            --z_index;
        }
    }
}

void GamePlugin::postUpdate()
{
    p_camera_kinematic->velocity().x = p_camera_speed;
    h2d::Transformation cam_transform = p_camera_kinematic->simulate(game().fixedUpdateLag());
    p_mogl->getCamera().setPosition(glm::vec3(cam_transform.x, cam_transform.y, -1));
    p_mogl->getCamera().setCenter(glm::vec3(cam_transform.x, cam_transform.y, 1));
    updateActiveActors();
}

void GamePlugin::setCameraSpeed(float speed)
{
    p_camera_speed = speed;
}

float GamePlugin::getCameraSpeed() const
{
    return p_camera_speed;
}


void GamePlugin::setActorFactory(ActorFactory& factory)
{
    p_factory = & factory;
}

void GamePlugin::addActor(h2d::Actor* actor)
{
    p_inactive_actors->insert(actor);
    actor->deactivate();
}

void GamePlugin::addCollider(Collider* collider)
{
    switch (collider->getType()) {
        case Collider::Type::PlayerBullet:
            p_player_bullet_collider->insert(collider);
            break;
        case Collider::Type::EnemyBullet:
            p_enemy_bullet_collider->insert(collider);
            break;
        case Collider::Type::Wall:
            p_wall_collider->insert(collider);
            break;
        case Collider::Type::Player:
            p_player_collider->insert(collider);
            break;
        case Collider::Type::Enemy:
            p_enemy_collider->insert(collider);
            break;
    }
}

void GamePlugin::removeCollider(Collider* collider)
{
    switch (collider->getType()) {
        case Collider::Type::PlayerBullet:
            p_player_bullet_collider->erase(collider);
            break;
        case Collider::Type::EnemyBullet:
            p_enemy_bullet_collider->erase(collider);
            break;
        case Collider::Type::Wall:
            p_wall_collider->erase(collider);
            break;
        case Collider::Type::Player:
            p_player_collider->erase(collider);
            break;
        case Collider::Type::Enemy:
            p_enemy_collider->erase(collider);
            break;
    }
}

void GamePlugin::updateActiveActors()
{
    float max = p_mogl->getCamera().getPosition().x + ORTHO_WIDTH + 3;

    std::vector<h2d::Actor*> to_remove;
    for (h2d::Actor* actor : *p_inactive_actors)
    {
        if (actor->transform().x < max)
        {
            actor->addBehavior<GameBehavior>();
            actor->activate();
            to_remove.push_back(actor);
        }
    }

    for(auto a : to_remove)
    {
        p_inactive_actors->erase(a);
    }
}

const tiled::Map& GamePlugin::getMap() const
{
    return p_active_map;
}

void GamePlugin::changeLevel(const std::string& name)
{
    p_change_level = true;
    p_next_level_name = name;
}
