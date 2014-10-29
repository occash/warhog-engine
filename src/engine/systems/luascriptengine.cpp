#include "luascriptengine.h"
#include "../input.h"

#include "../components/scriptcomponent.h"
#include "../components/cameracomponent.h"
#include "../components/lightcomponent.h"
#include "../components/materialcomponent.h"
#include "../components/meshfiltercomponent.h"
#include "../components/transformcomponent.h"

#include <lua/lua.hpp>

#include <luabind/detail/call_function.hpp>
#include <luabind/operator.hpp>
#include <luabind/detail/object_rep.hpp>
#include <luabind/detail/class_rep.hpp>

using namespace luabind;

struct ScriptComponentWrapper : BaseScript, luabind::wrap_base
{
    void start()
    {
        call<void>("start");
    }

	void default_start(BaseScript *ptr)
    {
		ptr->BaseScript::start();
    }

    void update()
    {
        call<void>("update");
    }

	void default_update(BaseScript *ptr)
    {
		ptr->BaseScript::update();
    }

    void stop()
    {
        call<void>("stop");
    }

	void default_stop(BaseScript *ptr)
    {
		ptr->BaseScript::stop();
    }

    void proxyObject() const
    {
        wrapped_self_t selfRef = luabind::detail::wrap_access::ref(*this);
        lua_State* l = selfRef.state();
        selfRef.get(l);

        luabind::object selfObj(luabind::from_stack(l, -1));
        selfObj.push(l);
        //int res = lua_getmetatable(l, -1);
        lua_getuservalue(l, -1);
        if (lua_istable(l, -1))
        {
            lua_pushnil(l);  // first key
            while (lua_next(l, -2) != 0)
            {
                // uses 'key' (at index -2) and 'value' (at index -1)
                std::cout << luaL_typename(l, -2) << ": " << luaL_typename(l, -1) << std::endl;

                int luaType = lua_type(l, -1);
                switch (luaType)
                {
                case LUA_TNUMBER:
                {
                    double arg = luaL_checknumber(l, -1);
                    lua_pop(l, 1);
                    lua_pushvalue(l, -1);
                    lua_pushnumber(l, arg * 0.5);
                    lua_rawset(l, -4);
                }
                    break;
                case LUA_TUSERDATA:
                {
                    /*Vector3d *val = object_cast<Vector3d *>(tmpVal);
                    std::cout << "Vector3(" << val->x << ", " << val->y << ", " << val->z << ")";*/
                    lua_pop(l, 1);
                }
                    break;
                default:
                    lua_pop(l, 1);
                    break;
                }
                // removes 'value'; keeps 'key' for next iteration
            }
            lua_pop(l, 1);
        }

        lua_pop(l, 1);
    }
};

//TODO: Lua panic handler
/*static jmp_buf lua_panic_jump;
static int lua_atpanic(lua_State *lua)
{
    longjmp(lua_panic_jump, 1);
    // will never return
    return 0;
}*/

LuaScriptEngine::LuaScriptEngine()
{
}


LuaScriptEngine::~LuaScriptEngine()
{
}

bool LuaScriptEngine::init()
{
    //Create Lua stack
    _state = luaL_newstate();
    if (nullptr == _state)
        return false;

    //Open standard libs
    luaL_openlibs(_state);
    //Init luabind lib
    luabind::open(_state);

    luaL_dofile(_state, "Engine.lua");

    return true;
}

bool LuaScriptEngine::bind()
{
    //Add wrapper of base Script class
    //in order to use it in scripts
    module(_state)
    [
        class_<BaseScript, ScriptComponentWrapper>("BaseComponent")
        .def(constructor<>())
		.def("start", &BaseScript::start,
        &ScriptComponentWrapper::default_start)
		.def("update", &BaseScript::update,
        &ScriptComponentWrapper::default_update)
		.def("stop", &BaseScript::stop,
        &ScriptComponentWrapper::default_stop)
		.property("camera", &BaseScript::getCamera)
		.property("light", &BaseScript::getLight)
		.property("material", &BaseScript::getMaterial)
		.property("meshFilter", &BaseScript::getMeshFilter)
		.property("transform", &BaseScript::getTransform),

        class_<Input>("Input")
        .scope
        [
            def("key", &Input::key),
            def("button", &Input::button),
            def("axis", &Input::axis)
        ]
        .enum_("Axis")
        [
            value("Horizontal", Input::Horizontal),
            value("Vertical", Input::Vertical)
        ]
        .enum_("Button")
        [
            value("Left", Input::Left),
            value("Middle", Input::Middle),
            value("Right", Input::Right),
            value("Special1", Input::Special1),
            value("Special2", Input::Special2),
            value("Special3", Input::Special3),
            value("Special4", Input::Special4),
            value("Special5", Input::Special5)
        ],

        class_<glm::vec3>("Vector3")
        .def(constructor<glm::float_t, glm::float_t, glm::float_t>())
        .def_readwrite("x", &glm::vec3::x)
        .def_readwrite("y", &glm::vec3::y)
        .def_readwrite("z", &glm::vec3::z)
        .def(self + glm::vec3())
        .def(self - glm::vec3()),

        //Components
        class_<CameraComponent>("Camera")
        .def(constructor<>())
        .enum_("ProjectionType")
        [
            value("Perspective", CameraComponent::Perspective),
            value("Ortho", CameraComponent::Ortho),
            value("Custom", CameraComponent::Custom)
        ]
        .property("progectionType", 
        &CameraComponent::projectionType, 
        &CameraComponent::setProjectionType)
        .property("fieldOfView",
        &CameraComponent::fieldOfView,
        &CameraComponent::setFieldOfView)
        .property("aspect",
        &CameraComponent::aspect,
        &CameraComponent::setAspect)
        .property("nearPlane",
        &CameraComponent::nearPlane,
        &CameraComponent::setNearPlane)
        .property("farPlane",
        &CameraComponent::farPlane,
        &CameraComponent::setFarPlane)
        .property("clearColor",
        &CameraComponent::clearColor,
        &CameraComponent::setClearColor),

        class_<TransformComponent>("Transform")
        .property("position", 
        &TransformComponent::position,
        &TransformComponent::setPosition)
        .property("rotation",
        &TransformComponent::rotation,
        &TransformComponent::setRotation)
        .property("scale",
        &TransformComponent::scale,
        &TransformComponent::setScale)
    ];

    return true;
}

bool LuaScriptEngine::shutdown()
{
    lua_close(_state);

    return true;
}

bool LuaScriptEngine::load(const std::string& name, const std::string& source)
{
    object obj = globals(_state)[name];
    if (obj == object())
        return true;

    int result = luaL_dostring(_state, source.c_str());
    if (result != 0)
    {
        std::cout << lua_tostring(_state, -1) << std::endl;
        lua_pop(_state, 1);
    }

    /*obj = globals(_state)[name];
    if (!obj.is_valid() || obj == object())
        return false;
    
    obj.push(_state);
    if (detail::is_class_rep(_state, -1))
    {
        detail::class_rep *crep = 
            (detail::class_rep *)lua_touserdata(_state, -1);
        crep->get_table(_state);
        object ctable(from_stack(_state, -1));

        for (iterator i(ctable), end; i != end; ++i)
        {
            std::string key = object_cast<std::string>(i.key());
            object value = *i;
            std::cout << key << (type(value) == LUA_TFUNCTION) << std::endl;
        }

        int ref = crep->metatable_ref();
        lua_getmetatable(_state, ref);

        object cmeta(from_stack(_state, -1));

        for (iterator i(cmeta), end; i != end; ++i)
        {
            std::string key = object_cast<std::string>(i.key());
            object value = *i;
            std::cout << key << (type(value) == LUA_TFUNCTION) << std::endl;
        }
    }*/

    return result == 0;
}

BaseScript *LuaScriptEngine::instance(const std::string& name)
{
    object obj;
	BaseScript *script;
    try 
    {
        obj = call_function<object>(_state, name.c_str());
		script = object_cast<BaseScript *>(obj);
        /*scr->proxyObject();
        object tmpObj = obj["lol"];
        double val = object_cast<double>(tmpObj);
        std::cout << "Test.lol = " << val << std::endl;*/
    }
    catch (const error& e)
    {
        object error_message(from_stack(e.state(), -1));
        std::cout << error_message << std::endl;
        return nullptr;
    }

    return script;
}

void LuaScriptEngine::collect(Ptr<ScriptComponent> script)
{
    script.reset();
    lua_gc(_state, LUA_GCCOLLECT, 0);
}
