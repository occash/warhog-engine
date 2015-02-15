#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <string>

#include "../components/scriptcomponent.h"

class BaseScript;

class ScriptEngine
{
public:
    ScriptEngine();
    ~ScriptEngine();

    virtual std::string name() const = 0;

    virtual bool init() = 0;
    virtual bool bind() = 0;
    virtual bool shutdown() = 0;

    virtual bool load(const std::string& name, const std::string& source) = 0;
    virtual BaseScript *instance(const std::string& name) = 0;
    virtual void collect(std::shared_ptr<ScriptComponent> script) = 0;

};

#endif
