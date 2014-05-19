#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "entityx/System.h"
#include "../global.h"
#include "../components/scriptcomponent.h"

#include <map>
#include <set>

class Script;
class ScriptEngine;

using namespace entityx;

class ScriptSystem : public System<ScriptSystem>
{
public:
    ScriptSystem();
    ~ScriptSystem();

    void configure(ptr<EventManager> events);
    void update(ptr<EntityManager> entities, ptr<EventManager> events, double dt) override;

    template<class Engine>
    void registerEngine();

    ptr<ScriptComponent> assign(Entity entity, Ptr<Script> script);

private:
    void registerEngine(ScriptEngine *engine);

private:
    typedef std::map<std::string, Ptr<ScriptEngine>> EngineList;
    EngineList _engines;

};

template<class Engine>
void ScriptSystem::registerEngine()
{
    registerEngine(new Engine());
}

#endif
