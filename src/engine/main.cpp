#include "systems/rendersystem.h"
#include "systems/inputsystem.h"
#include "systems/scriptsystem.h"

#include <entityx/Manager.h>
#include <entityx/deps/Dependencies.h>
#include <GLFW/glfw3.h>

#include "mesh.h"
#include "components/transformcomponent.h"
#include "components/cameracomponent.h"
#include "components/meshfiltercomponent.h"
#include "components/materialcomponent.h"
#include "components/renderercomponent.h"
#include "components/lightcomponent.h"

#include "meshimporter.h"
#include "glcontext.h"
#include "input.h"
#include "systems/luascriptengine.h"

#include "resourcemanager.h"
#include "resource/meshresource.h"
#include "resource/scriptresource.h"

#include <boost/any.hpp>
#include "tree.h"

using namespace entityx;

/*class SceneEntity
{
    tree<Entity>::iterator node;
    tree<Entity> *tree;
};

class Scene
{
public:
    Scene() : _entityFactory(new EntityManager())
    {
    }

    Ptr<SceneEntity> createEntity()
    {
        Entity id = _entityFactory->create();
        _tree->insert(_tree.end(), id);
        Ptr<SceneEntity> entity(new SceneEntity());
    }

private:
    Ptr<EntityManager> _entityFactory;
    tree<Entity> _tree;
};*/

class GameManager : public Manager {
protected:
	void configure() {
        GLContextHints contextHints;
        GLFramebufferHints frameHints;
        GLWindowHints windowHints;

        YAML::Node doc = YAML::LoadFile("config.yaml");
        /*auto iter = doc.begin();
        for (; iter != doc.end(); ++iter)
        {
            std::cout << iter->first.as<std::string>() << std::endl;
            std::cout << iter->first.Type();
        }*/
        doc["OpenGL context"] >> contextHints;
        doc["Frame buffer"] >> frameHints;
        doc["Window options"] >> windowHints;

        _context = Ptr<GLContext>(new GLContext(
            contextHints,
            frameHints));
        _window = Ptr<Window>(new Window(
            windowHints));

        //TODO: create key manager
        std::map<std::string, int> keyMap;
        keyMap.insert(std::make_pair("up", GLFW_KEY_W));
        keyMap.insert(std::make_pair("down", GLFW_KEY_S));
        keyMap.insert(std::make_pair("left", GLFW_KEY_A));
        keyMap.insert(std::make_pair("right", GLFW_KEY_D));

        bool result = _context->makeCurrent(_window);
        if (!result)
            exit(2);

        system_manager->add<InputSystem>(_window, keyMap);
        ptr<ScriptSystem> scripting = system_manager->add<ScriptSystem>();
        scripting->registerEngine<LuaScriptEngine>();
        system_manager->add<RenderSystem>(_window);
	}

	void initialize() {
        tree<Entity> entities;

		Entity cameraId = entity_manager->create();
		auto cameraPos = cameraId.assign<TransformComponent>();
        auto camera = cameraId.assign<CameraComponent>();
        entities.insert(entities.end(), cameraId);

		camera->setClearColor(glm::vec3(0.0f, 0.0f, 0.0f));
		camera->setFarPlane(1000.0f);
		camera->setFieldOfView(60.0f);

        cameraPos->setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
        cameraPos->setRotation(glm::vec3(45.0f, 45.0f, 0.0f));

        Entity lightId = entity_manager->create();
        auto lightPos = lightId.assign<TransformComponent>();
        auto light = lightId.assign<LightComponent>();
        auto lightNode = entities.insert(entities.end(), lightId);

        light->setType(LightComponent::Directional);
        light->setColor(glm::vec4(1.0f, 0.5f, 0.5f, 0.0f));
        light->setIntensity(1.0f);
        lightPos->setRotation(glm::vec3(0.0f, 135.0f, 0.0f));

        ResourceManager manager;
        manager.add<MeshResource>();
        manager.add<ScriptResource>();

        Ptr<Mesh> mesh = manager.load<Mesh>("dragon.bmf");
        Ptr<Script> script = manager.load<Script>("Test.lua");
        script->engine = "lua";
        script->name = "Test";
        Mesh *cube = mesh.get();

		Entity modelId = entity_manager->create();
		modelId.assign<TransformComponent>();
        auto meshFilter = modelId.assign<MeshFilterComponent>();
        auto material = modelId.assign<MaterialComponent>();
        auto renderer = modelId.assign<RendererComponent>();
        entities.append_child(lightNode, modelId);

        //TODO: remake mesh loading
		meshFilter->setMesh(cube);
		material->setShader("shaders/brdf");
		renderer->loadData(cube);

        //Entity scriptId = entity_manager->create();
        auto sysptr = system_manager->system<ScriptSystem>();
        ptr<ScriptSystem> scriptSystem(static_pointer_cast<ScriptSystem>(sysptr));
        scriptSystem->assign(cameraId, script);

        /*for (auto entity : entities)
        {
            std::cout << entity.id() << std::endl;
        }*/
	}

	void update(double dt) {
        if (_window->isClosing())
        {
            stop();
            return;
        }
        system_manager->update<InputSystem>(dt);
        system_manager->update<ScriptSystem>(dt);
		system_manager->update<RenderSystem>(dt);
	}

private:
    Ptr<GLContext> _context;
    Ptr<Window> _window;
    Ptr<Input> _input;

};

int main()
{
	GameManager game;
	game.start();
	game.run();

    /*DWORD previous = GetTickCount();
    DWORD lag = 0.0;
    while (true)
    {
        DWORD current = GetTickCount();
        DWORD elapsed = current - previous;
        previous = current;
        lag += elapsed;

        //processInput();

        while (lag >= MS_PER_UPDATE)
        {
            //update();
            lag -= MS_PER_UPDATE;
        */

        //w.render(&camera, &cubeModel);
    //}


    return 0;
}