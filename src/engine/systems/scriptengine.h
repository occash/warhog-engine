#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <string>

#include "../components/scriptcomponent.h"

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
    virtual ptr<ScriptComponent> instance(const std::string& name) = 0;
    virtual void collect(ptr<ScriptComponent> script) = 0;

};

#endif
