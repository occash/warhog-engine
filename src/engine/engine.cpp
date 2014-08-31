#include "engine.h"

//Systems
#include "systems/inputsystem.h"
#include "systems/rendersystem.h"
#include "systems/scriptsystem.h"

//Components
#include "components/transformcomponent.h"
#include "components/cameracomponent.h"
#include "components/meshfiltercomponent.h"
#include "components/materialcomponent.h"
#include "components/renderercomponent.h"
#include "components/lightcomponent.h"

//Engine objects
#include "mesh.h"
#include "shader.h"
#include "material.h"

//Resources
#include "resourcemanager.h"
#include "resource/meshresource.h"

std::string readFile(const std::string& fileName)
{
	std::string source;
	std::ifstream file(fileName);
	if (file.is_open())
	{
		source = std::string((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		file.close();
	}

	return source;
}

void Engine::start()
{
	configure();
	systems.configure();
	initialize();
}

int Engine::run()
{
	_running = true;
	while (_running) {
		std::clock_t ticks = std::clock();
		update(double(ticks - _timer) / CLOCKS_PER_SEC);
		_timer = ticks;
	}

	return 0;
}

void Engine::step(double dt)
{
	update(dt);
}

void Engine::stop()
{
	_running = false;
}

void Engine::configure()
{
	//TODO: create key manager
	//std::map<std::string, int> keyMap;
	//keyMap.insert(std::make_pair("up", GLFW_KEY_W));
	//keyMap.insert(std::make_pair("down", GLFW_KEY_S));
	//keyMap.insert(std::make_pair("left", GLFW_KEY_A));
	//keyMap.insert(std::make_pair("right", GLFW_KEY_D));

	//systems.add<InputSystem>(_window, keyMap);
	//Ptr<ScriptSystem> scripting = systems.add<ScriptSystem>();
	//scripting->registerEngine<LuaScriptEngine>();
	systems.add<RenderSystem>();
	systems.system<RenderSystem>()->chooseBackend("OpenGL"); //TODO: read from config
}

void Engine::initialize()
{
	//Create camera
	Entity cameraId = entities.create();
	auto cameraPos = cameraId.assign<TransformComponent>();
	auto camera = cameraId.assign<CameraComponent>();

	camera->setClearColor(glm::vec3(0.0f, 0.0f, 0.5f));
	camera->setFarPlane(1000.0f);
	camera->setFieldOfView(60.0f);

	cameraPos->setPosition(glm::vec3(-1.0f, 1.0f, 1.0f));
	cameraPos->setRotation(glm::vec3(45.0f, 45.0f, 0.0f));

	//Create light
	Entity lightId = entities.create();
	auto lightPos = lightId.assign<TransformComponent>();
	auto light = lightId.assign<LightComponent>();

	light->setType(LightComponent::Directional);
	light->setColor(glm::vec4(1.0f, 0.5f, 0.5f, 0.0f));
	light->setIntensity(0.1f);
	lightPos->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));

	//Create model
	Entity modelId = entities.create();
	modelId.assign<TransformComponent>();
	auto meshFilter = modelId.assign<MeshFilterComponent>();
	auto material = modelId.assign<MaterialComponent>();

	//ResourceManager manager;
	//manager.add<MeshResource>();
	//manager.add<ScriptResource>();
	Renderer *renderer = systems.system<RenderSystem>()->renderer();
	MeshResource meshResource(renderer);
	std::ifstream meshIn("D:/projects/warhog-engine/test/project1/resources/models/dragon_assimp", std::ios::binary | std::ios::in);
	Object *meshObject = nullptr;
	meshResource.load(meshIn, meshObject);
	Mesh *cube = static_cast<Mesh*>(meshObject);
	cube->load();
	meshFilter->setMesh(cube);

	Shader *shader = renderer->createShader();
	shader->vertexSource = readFile("D:/projects/warhog-engine/src/engine/shaders/brdf.vert");
	shader->pixelSource = readFile("D:/projects/warhog-engine/src/engine/shaders/brdf.frag");
	shader->load();

	Material *mat = new Material;
	mat->setShader(shader);
	material->setMaterial(mat);
	mat->setProperty("color", glm::vec3(0.9f, 0.5f, 0.55f) / 3.14f);
	float refractiveIndex = 16.0f;
	float fresnel0 = ((1.0f - refractiveIndex) / (1.0f + refractiveIndex));
	fresnel0 = fresnel0 * fresnel0;
	mat->setProperty("fresnel0", fresnel0);
	mat->setProperty("roughness", 0.25f);

	//Entity scriptId = entity_manager->create();
	//auto scriptSystem = systems.system<ScriptSystem>();
	//scriptSystem->assign(cameraId, script);
}

void Engine::update(double dt)
{
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
