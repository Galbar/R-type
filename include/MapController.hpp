#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "..."

class MapController
{
public:
    MapController();
    ~MapController();

    float getVersion();
    float getLuaVersion();
    float getTiledVersion();
    std::string getOrientation();
    std::string getRenderorder();
    int getWidth();
    int getHeight();
    int getTileWidth();
    int getTileHeight();
    int getHexSideLength();
    std::string getStaggerAxis();
    std::string getStaggerIndex();
    std::string getBackgroundColor();//hexadecimal
    int getNextObjectId(); //Actualizamos???

//properties

//tilesset

//layers

//objectgroup

//imagelayer

private:
    float p_version, p_lua_version, p_tiled_version;
    std::string p_orientation, p_render_order;
    int p_width, p_height, p_next_object_id;

    std::map< std::string, Property> p_properties;

    std::map< std::string, TileSet> p_tiles;

    std::map< std::string, Layer> p_layers;

    std::map< std::string, Object> p_objects;

    std::map< std::string, Image> p_images;

    struct Property
    {
    };

    struct TileSet
    {
        int p_first_g_id;
        std::string p_file_name;
        int p_tile_width;
        int p_tile_height;
        int p_spacing;
        int p_margin;

        int p_tile_offset_x;
        int p_tile_offset_y;
1
        std::string p_image;
        int p_image_width;
        int p_image_height;
////////////////////////////////////////

        int p_tile_count;
        int p_columns;

        map<std::string, Property> p_properties;

        map< std::string, Terrain> p_terrains;

        map< std::string, Tile> p_tile;

        struct Terrain {
            int p_tile_num;
            map< std::string, Property> p_properties;
        };

        struct Tile {
            std::string p_terrain;
            float p_probability;

            map< std::string, Property> p_properties;

            Image p_image;

            Object p_object;

            ///////Animation p_animation;
        };
    };

    struct Layer
    {
        std::string p_type;
        int p_x, p_y;
        int p_width, p_height;
        float p_opacity;
        int p_visible;
        int p_offset_x, p_offset_y;

        map< std::string, Property> p_properties;

        std::string p_encoding;
        std::string p_data;
    };

/*    struct Object
    {
    };

    struct Image
    {
    };
*/
};

#endif
