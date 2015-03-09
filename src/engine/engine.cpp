#include "engine.h"

//Systems
#include "systems/rendersystem.h"
#include "systems/scriptsystem.h"

//Components
#include "components/infocomponent.h"
#include "components/transformcomponent.h"
#include "components/cameracomponent.h"
#include "components/meshfiltercomponent.h"
#include "components/materialcomponent.h"
#include "components/lightcomponent.h"

//Engine objects
#include "mesh.h"
#include "shader.h"
#include "material.h"

//Resources
#include "resourcemanager.h"
#include "resource/meshresource.h"
#include "resource/textureresource.h"

#include "math/vector.h"
#include "math/matrix.h"

#include "Geometry.h"

using namespace entityx;

//Choose the best graphics card available on PC
extern "C"
{
    DECL_EXPORT int AmdPowerXpressRequestHighPerformance = 1;
    DECL_EXPORT int NvOptimusEnablement = 0x00000001;
}

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
    _elapsed = 0.0;
    configure();
    systems.configure();
    initialize();
}

int Engine::run()
{
    systems.system<RenderSystem>()->window()->show();

    _running = true;
    while (_running && systems.system<RenderSystem>()->window()->isVisible())
    {
        _app.update();
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
    std::shared_ptr<ScriptSystem> scripting = systems.add<ScriptSystem>();
    //scripting->registerEngine<LuaScriptEngine>();
    systems.add<RenderSystem>();
    systems.system<RenderSystem>()->chooseBackend("OpenGL"); //TODO: read from config
    _window = systems.system<RenderSystem>()->window();
}

void Engine::initialize()
{
    //Create camera
    Entity cameraId = entities.create();
    auto cameraInfo = cameraId.assign<InfoComponent>("Main camera");
    auto cameraPos = cameraId.assign<TransformComponent>();
    auto camera = cameraId.assign<CameraComponent>();

    camera->setClearColor(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->setNearPlane(0.1f);
    camera->setFarPlane(100.0f);
    camera->setFieldOfView(60.0f);

    cameraPos->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    cameraPos->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));

    //Create light
    Entity lightId = entities.create();
    lightId.assign<InfoComponent>("Light");
    _lightNode = lightId;
    auto lightPos = lightId.assign<TransformComponent>();
    auto light = lightId.assign<LightComponent>();
    light->setType(LightComponent::Directional);
    light->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
    light->setIntensity(0.1f);
    //lightPos->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
    //lightPos->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));

    //Create model
    Entity modelId = entities.create();
    modelId.assign<InfoComponent>("Dragon");
    modelId.assign<TransformComponent>();
    auto meshFilter = modelId.assign<MeshFilterComponent>();
    auto material = modelId.assign<MaterialComponent>();

    //ResourceManager manager;
    //manager.add<MeshResource>();
    //manager.add<ScriptResource>();
    Renderer *renderer = systems.system<RenderSystem>()->renderer();
    MeshResource meshResource(renderer);
    std::ifstream meshIn("resources/dragon", std::ios::binary | std::ios::in);
    Object *meshObject = nullptr;
    meshResource.load(meshIn, meshObject);

    Mesh *cube = static_cast<Mesh *>(meshObject);
    Geometry m_geometry(renderer);
    //Mesh *cube = m_geometry.cube(2, 2, 2);
    cube->load();
    meshFilter->setMesh(cube);

    Shader *shader = renderer->createShader();
    shader->vertexSource = readFile("resources/shaders/brdf.vert");
    shader->pixelSource = readFile("resources/shaders/brdf.frag");
    shader->load();

    mat = new Material;
    mat->setShader(shader);
    material->setMaterial(mat);
    mat->setProperty("color", glm::vec3(0.6f, 0.84f, 0.91f) / 3.14f);
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
    /*  DWORD previous = GetTickCount();
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
    /*  if (_window->update())
        {
        stop();
        return;
        }*/
    //systems.update<InputSystem>(dt);
    //systems.update<ScriptSystem>(dt);
    //auto lightPos = _lightNode.component<TransformComponent>();
    //glm::vec3 rot = lightPos->rotation();
    //rot.y = rot.y + 1;
    //lightPos->setRotation(rot);

    _elapsed += dt;
    if (_elapsed >= 4)
    {
        float refractiveIndex = std::rand() % 20 + 0.01;
        float roughness = 0.1f * (std::rand() % 10) + 0.01;
        float fresnel0 = ((1.0f - refractiveIndex) / (1.0f + refractiveIndex));
        fresnel0 = fresnel0 * fresnel0;

        mat->setProperty("fresnel0", fresnel0);
        mat->setProperty("roughness", roughness);

        _elapsed = 0.0;
    }

    /*  auto lightPos = _lightNode.component<TransformComponent>();
        glm::vec3 rot = lightPos->rotation();
        rot.y = rot.y + 1;
        if (rot.y == 360)
        rot.y = 0;
        lightPos->setRotation(rot);*/

    systems.update<RenderSystem>(dt);
    systems.update<ScriptSystem>(dt);
}

Window *Engine::window() const
{
    return _window;
}

void Engine::createEntity(const std::string& name)
{
    Entity entityId = entities.create();
    entityId.assign<InfoComponent>(name);
    entityId.assign<TransformComponent>();
}

void Engine::addComponent(entityx::Entity id, const std::string& name)
{
    if (name == "Camera")
        id.assign<CameraComponent>();
    if (name == "Light")
        id.assign<LightComponent>();
    if (name == "Material")
        id.assign<MaterialComponent>();
    if (name == "Mesh")
        id.assign<MeshFilterComponent>();
    if (name == "Script")
        id.assign<ScriptComponent>();
}
