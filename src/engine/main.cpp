#include "systems/rendersystem.h"
#include "systems/inputsystem.h"
#include "systems/scriptsystem.h"

#include <entityx/quick.h>
#include <entityx/deps/Dependencies.h>
#include <GLFW/glfw3.h>

#include "mesh.h"
#include "components/transformcomponent.h"
#include "components/cameracomponent.h"
#include "components/meshfiltercomponent.h"
#include "components/materialcomponent.h"
#include "components/renderercomponent.h"
#include "components/lightcomponent.h"

#include "render/opengl/glcontext.h"
#include "input.h"
#include "systems/luascriptengine.h"

#include "resourcemanager.h"
#include "resource/meshresource.h"
#include "resource/scriptresource.h"

#include "tree.h"
#include <ctime>

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

class GameManager : public EntityX {
public:
	void configure() {
        GLContextHints contextHints;
        GLFramebufferHints frameHints;
        GLWindowHints windowHints;

        YAML::Node doc = YAML::LoadFile("D:\\projects\\warhog-engine\\src\\engine\\config.yaml");
        /*auto iter = doc.begin();
        for (; iter != doc.end(); ++iter)
        {
            std::cout << iter->first.as<std::string>() << std::endl;
            std::cout << iter->first.Type();
        }*/
        doc["OpenGL context"] >> contextHints;
        doc["Frame buffer"] >> frameHints;
        doc["Window options"] >> windowHints;

        /*_context = Ptr<GLContext>(new GLContext(
            contextHints,
            frameHints));
        _window = Ptr<Window>(new Window(
			Window::Closable | Window::Resizable));*/

        //TODO: create key manager
        std::map<std::string, int> keyMap;
        keyMap.insert(std::make_pair("up", GLFW_KEY_W));
        keyMap.insert(std::make_pair("down", GLFW_KEY_S));
        keyMap.insert(std::make_pair("left", GLFW_KEY_A));
        keyMap.insert(std::make_pair("right", GLFW_KEY_D));

        //bool result = _context->makeCurrent(_window);
        /*if (!result)
            exit(2);*/

        //systems.add<InputSystem>(_window, keyMap);
		//Ptr<ScriptSystem> scripting = systems.add<ScriptSystem>();
        //scripting->registerEngine<LuaScriptEngine>();
		systems.add<RenderSystem>();

		//_window->show();
	}

	void initialize() {
       /* tree<Entity> entitieTree;

		Entity cameraId = entities.create();
		auto cameraPos = cameraId.assign<TransformComponent>();
        auto camera = cameraId.assign<CameraComponent>();
        entitieTree.insert(entitieTree.end(), cameraId);

		camera->setClearColor(glm::vec3(0.0f, 0.0f, 0.0f));
		camera->setFarPlane(1000.0f);
		camera->setFieldOfView(60.0f);

        cameraPos->setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
        cameraPos->setRotation(glm::vec3(45.0f, 45.0f, 0.0f));

		Entity lightId = entities.create();
        auto lightPos = lightId.assign<TransformComponent>();
        auto light = lightId.assign<LightComponent>();
        auto lightNode = entitieTree.insert(entitieTree.end(), lightId);

        light->setType(LightComponent::Directional);
        light->setColor(glm::vec4(1.0f, 0.5f, 0.5f, 0.0f));
        light->setIntensity(1.0f);
        lightPos->setRotation(glm::vec3(0.0f, 135.0f, 0.0f));

        /*ResourceManager manager;
        manager.add<MeshResource>();
        manager.add<ScriptResource>();*/

		/*Ptr<Mesh> mesh;// = manager.load<Mesh>("dragon.bmf");
		Ptr<Script> script;// = manager.load<Script>("Test.lua");
        script->engine = "lua";
        script->name = "Test";
        Mesh *cube = mesh.get();

		Entity modelId = entities.create();
		modelId.assign<TransformComponent>();
        auto meshFilter = modelId.assign<MeshFilterComponent>();
        auto material = modelId.assign<MaterialComponent>();
        auto renderer = modelId.assign<RendererComponent>();
        entitieTree.append_child(lightNode, modelId);

        //TODO: remake mesh loading
		meshFilter->setMesh(cube);
		material->setShader("shaders/brdf");
		renderer->loadData(cube);

        //Entity scriptId = entity_manager->create();
		auto scriptSystem = systems.system<ScriptSystem>();
		scriptSystem->assign(cameraId, script);*/
	}

	void update(double dt) {
		//_window->update();
        /*if (_window->update())
        {
            stop();
            return;
        }*/
        //systems.update<InputSystem>(dt);
		//systems.update<ScriptSystem>(dt);
		systems.update<RenderSystem>(dt);
	}

	void start() {
		configure();
		systems.configure();
		initialize();
	}

	void run() {
		_running = true;
		while (_running) {
			std::clock_t ticks = std::clock();
			update(double(ticks - _timer) / CLOCKS_PER_SEC);
			_timer = ticks;
		}
	}

	void step(double dt) {
		update(dt);
	}


	void stop() {
		_running = false;
	}

private:
    Ptr<GLContext> _context;
    Ptr<Window> _window;
    Ptr<Input> _input;
	std::clock_t _timer;
	bool _running = false;

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