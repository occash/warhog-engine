#include "scriptsystem.h"
#include "../script.h"
#include "luascriptengine.h"

#include <lua/lua.hpp>
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

void ScriptSystem::configure(EventManager &events)
{
    auto _state = _engines.begin();
    for (; _state != _engines.end(); ++_state) {
        auto engine = _state->second;

        engine->init();
        engine->bind();
    }
}

void ScriptSystem::update(EntityManager &manager, EventManager &events, double dt)
{
	auto entities = manager.entities_with_components<ScriptComponent>();

	for (auto i = entities.begin(); i != entities.end(); ++i)
	{
		auto script = (*i).component<ScriptComponent>();
		for (BaseScript *base : script->scripts)
			base->update();
	}
}

void ScriptSystem::registerEngine(ScriptEngine *engine)
{
    Ptr<ScriptEngine> enginePtr(engine);
    _engines.insert(std::make_pair(engine->name(), enginePtr));
}

bool ScriptSystem::assign(Entity entity, Ptr<Script> script)
{
    auto enginePair = _engines.find(script->engine);
	if (enginePair == _engines.end())
		return false;

    auto engine = enginePair->second;
	if (!entity.has_component<ScriptComponent>())
		entity.assign<ScriptComponent>();

	if (!engine->load(script->name, script->source))
		return false;

	auto component = entity.component<ScriptComponent>();
	auto scriptObject = engine->instance(script->name);
	if (!scriptObject)
		return false;

	scriptObject->entity = entity;
	component->scripts.push_back(scriptObject);

	return true;
}
