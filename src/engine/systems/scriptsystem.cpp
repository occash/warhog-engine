#include "scriptsystem.h"
#include "../script.h"
#include "luascriptengine.h"

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <fstream>

using namespace luabind;

ScriptSystem::ScriptSystem()
{
}


ScriptSystem::~ScriptSystem()
{
    auto _state = _engines.begin();
    for (; _state != _engines.end(); ++_state) {
        auto engine = _state->second;

        engine->shutdown();
    }
}

void ScriptSystem::configure(ptr<EventManager> events)
{
    auto _state = _engines.begin();
    for (; _state != _engines.end(); ++_state) {
        auto engine = _state->second;

        engine->init();
        engine->bind();
    }
}

void ScriptSystem::update(ptr<EntityManager> manager, ptr<EventManager> events, double dt)
{
    for (BaseComponent::Family f = ScriptComponent::maxComponents();
        f < ENTITYX_MAX_COMPONENTS; ++f)
    {
        auto mask = manager->component_mask(f);
        auto entities = manager->entities_with_mask(mask);

        for (auto i = entities.begin(); i != entities.end(); ++i)
        {
            auto script = (*i).component<ScriptComponent>(f);
            try
            {
                script->update();
            }
            catch (luabind::error e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
}

void ScriptSystem::registerEngine(ScriptEngine *engine)
{
    Ptr<ScriptEngine> enginePtr(engine);
    _engines.insert(std::make_pair(engine->name(), enginePtr));
}

ptr<ScriptComponent> ScriptSystem::assign(Entity entity, Ptr<Script> script)
{
    auto enginePair = _engines.find(script->engine);
    if (enginePair == _engines.end())
        return ptr<ScriptComponent>();

    auto engine = enginePair->second;

    auto mask = entity.component_mask();
    for (BaseComponent::Family i = ScriptComponent::maxComponents();
        i < ENTITYX_MAX_COMPONENTS; ++i)
    {
        if (!mask[i])
        {
            if (!engine->load(script->name, script->source))
                return ptr<ScriptComponent>();

            auto component = engine->instance(script->name);
            if (component)
            {
                component->entity = entity;
                entity.set<ScriptComponent>(component, i);
            }
            return component;
        }
    }

    return ptr<ScriptComponent>();
}
