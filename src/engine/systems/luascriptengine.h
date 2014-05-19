#ifndef LUASCRIPTENGINE_H
#define LUASCRIPTENGINE_H

#include <map>
#include <luabind/luabind.hpp>

#include "../global.h"
#include "scriptengine.h"

class LuaScriptEngine : public ScriptEngine
{
public:
    LuaScriptEngine();
    ~LuaScriptEngine();

    std::string name() const { return "lua"; }

    bool init();
    bool bind();
    bool shutdown();

    bool load(const std::string& name, const std::string& source);
    ptr<ScriptComponent> instance(const std::string& name);
    void collect(ptr<ScriptComponent> script);

private:
    lua_State *_state;

};

#endif
