#ifndef ACTOR_FACTORY_HPP
#define ACTOR_FACTORY_HPP
#include <unordered_map>
#include "Hum2D/Hum2D.hpp"
#include "tiled/tiled.hpp"

class ActorConstructor
{
public:
    virtual ~ActorConstructor();
    virtual void construct(h2d::Actor&, const tiled::Object&) =0;
};

class ActorFactory
{
public:
    ActorFactory();
    ~ActorFactory();
    void build(const std::string& name, h2d::Actor&, const tiled::Object&);

    template <typename T>
    void set(const std::string& name)
    {
        p_builders.emplace(name, new T());
    }

private:
    std::unordered_map<std::string, ActorConstructor*> p_builders;
};
#endif
