#include "ActorFactory.hpp"

ActorConstructor::~ActorConstructor()
{}

ActorFactory::ActorFactory()
{}

ActorFactory::~ActorFactory()
{
    for (auto it : p_builders)
    {
        delete it.second;
    }
}

void ActorFactory::build(const std::string& name, h2d::Actor& actor, const tiled::Object& object)
{
    auto it = p_builders.find(name);
    if (it == p_builders.end())
    {
        actor.game().destroy(&actor);
        h2d_log("Builder " << name << " not found. Not building.");
        return;
    }
    it->second->construct(actor, object);
}
