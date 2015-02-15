#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "../global.h"
#include "../components/scriptcomponent.h"

#include <entityx/System.h>
#include <map>
#include <set>

class Script;
class ScriptEngine;

class ScriptSystem :
    public entityx::System<ScriptSystem>
{
public:
    ScriptSystem();
    ~ScriptSystem();

    void configure(entityx::EventManager& events) override;
    void update(entityx::EntityManager& entities,
                entityx::EventManager& events, double dt) override;

    template<class Engine>
    void registerEngine();

    bool assign(entityx::Entity entity, std::shared_ptr<Script> script);

private:
    void registerEngine(ScriptEngine *engine);

private:
    typedef std::map<std::string, std::shared_ptr<ScriptEngine>> EngineList;
    EngineList _engines;

};

template<class Engine>
void ScriptSystem::registerEngine()
{
    registerEngine(new Engine());
}

#endif
