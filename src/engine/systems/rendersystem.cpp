#include "rendersystem.h"
#include "../components/transformcomponent.h"
#include "../components/cameracomponent.h"
#include "../components/meshfiltercomponent.h"
#include "../components/materialcomponent.h"
#include "../components/lightcomponent.h"

#include "../mesh.h"
#include "../shader.h"
#include "../material.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.inl>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../render/opengl/glrenderer.h"
#include "../render/opengl/glextensions.h"
#include "../resource/textureresource.h"
#include "../material.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

using namespace entityx;

static std::string readFile(const std::string& fileName)
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

struct RenderInfo
{
    RenderInfo() :
        mesh(nullptr)
    {}
    ~RenderInfo()
    {
        delete mesh;
    }

    Mesh *mesh;
};

struct RenderQuad
{
    void create()
    {
        static const float verticies[] =
        {
            -1.0, -1.0, 0.5, 1.0,
            1.0, -1.0, 0.5, 1.0,
            -1.0, 1.0, 0.5, 1.0,
            1.0, 1.0, 0.5, 1.0
        };
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(Vertex), verticies, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void draw()
    {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    void destroy()
    {
        glBindVertexArray(_vao);

        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);

        glBindVertexArray(0);
    }

    GLuint _vao;
    GLuint _vbo;
};

RenderQuad renderQuad;

struct MaterialBlock
{
    glm::vec3 color;
    glm::float_t fresnel0;
    glm::float_t roughness;
    glm::float_t __padding1[3];
};

struct SkyboxBlock
{
    glm::mat4 view;
    float fov;
    float width;
    float height;
    float _padding0;
};

void applyTransform(glm::mat4& block, glm::vec3 move, glm::vec3 rotate, glm::vec3 scale)
{
    block = glm::translate(block, move);
    block = glm::rotate(block, -rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    block = glm::rotate(block, -rotate.y, glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, -rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::scale(block, scale);
}

void RenderSystem::renderSkyBox()
{
    /*  _skyShader->bind();
        ShaderBlock *skyMatrices = _skyShader->block("MatrixBlock");
        skyMatrices->set(&m, sizeof(MatrixBlock));
        _skyMesh->draw();
        _skyShader->unbind();*/
}

RenderSystem::RenderSystem() :
    _renderer(nullptr),
    _window(nullptr)
{
}

RenderSystem::~RenderSystem()
{
    renderQuad.destroy();
}

void RenderSystem::configure(EventManager& events)
{
    events.subscribe<EntityCreatedEvent>(*this);
    events.subscribe<EntityDestroyedEvent>(*this);
    events.subscribe<ComponentAddedEvent<MeshFilterComponent>>(*this);
    events.subscribe<ComponentRemovedEvent<MeshFilterComponent>>(*this);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);

    glClear(GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < 64; ++i)
    {
        pointLightBlock[i].intensity = 0;
        spotLightBlock[i].intensity = 0;
        directLightBlock[i].intensity = 0;

        pointLightBlock[i].color = glm::vec4{ 0, 0, 0, 0 };
        spotLightBlock[i].color = glm::vec4{ 0, 0, 0, 0 };
        directLightBlock[i].color = glm::vec4{ 0, 0, 0, 0 };

        spotLightBlock[i].shadowPower = 0;
    }
}


void *RenderSystem::getStucture(LightType lightType)
{
    switch (lightType)
    {
    case Directional:
        return (void *)(&directLightBlock[directLightInd++]);
        break;
    case Point:
        return (void *)(&pointLightBlock[pointLightInd++]);
        break;
    case Spot:
        return (void *)(&spotLightBlock[spotLightInd++]);
        break;
    default:
        break;
    }

    return nullptr;
}

LightInterface *RenderSystem::getNewInterface(LightType lightType)
{
    LightInterface *newLightInterface = new LightInterface(this);
    //newLightInterface->setType(lightType);

    return newLightInterface;
}

void RenderSystem::updateLight(entityx::EntityManager& entities, const MatrixBlock& m)
{
    auto lightCollection = entities.entities_with_components<LightComponent>();

    for (auto singleLight : lightCollection)
    {
        auto lightComp = singleLight.component<LightComponent>();

        if (lightComp->type() != Directional)
        {
            auto transformComp = singleLight.component<TransformComponent>();
            lightComp->getLightInterface()->setPosition((m.view * glm::vec4{ transformComp->position(), 1.0 }));
        }

        if (lightComp->type() != Point)
        {
            auto transformComp = singleLight.component<TransformComponent>();
            glm::vec3 lightDir = transformComp->direction();

            lightComp->getLightInterface()->setDirection(m.view * glm::vec4{ lightDir, 0.0 });
        }
    }
}

void RenderSystem::update(EntityManager& entities, EventManager& events, double dt)
{
    //Setup camera
    auto cameras = entities.entities_with_components<TransformComponent, CameraComponent>();
    auto cameraObject = cameras.begin();
    if (cameraObject == cameras.end())
        return;

    auto camTransform = (*cameraObject).component<TransformComponent>();
    auto camera = (*cameraObject).component<CameraComponent>();

    MatrixBlock m;

    glm::vec3 camPos = camTransform->position();

    glm::vec3 camRot = camTransform->rotation();

    glm::vec3 viewDir = glm::vec3(0.0f, 0.0f, -0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    //yaw
    viewDir = glm::rotate(viewDir, camRot.x, glm::vec3(0.0f, 1.0f, 0.0f));
    //pitch
    viewDir = glm::rotate(viewDir, camRot.y, glm::vec3(1.0f, 0.0f, 0.0f));
    //roll
    /*  cameraUp = glm::normalize(glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), viewDir));
        cameraUp = glm::rotate(cameraUp, camRot.z, glm::vec3(0.0f, 0.0f, 1.0f));*/

    glm::mat4 view = glm::lookAt(
                         camPos,
                         glm::vec3(0, 0, 0),
                         cameraUp
                     );

    camera->setAspect(float(_window->width()) / float(_window->height()));

    glm::mat4 model = glm::mat4(1.0f);
    m.model = model;
    m.view = view;
    m.projection = glm::perspective(
                       camera->fieldOfView(),
                       camera->aspect(),
                       camera->nearPlane(),
                       camera->farPlane()
                   );

    glm::vec3 color = camera->clearColor();

    glClearColor(color.x, color.y, color.z, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*  _skyShader->bind();
        SkyboxBlock sky;
        sky.fov = camera->fieldOfView();
        sky.width = _window->width();
        sky.height = _window->height();
        sky.view = glm::inverse(view);
        ShaderBlock *skyMatrices = _skyShader->block("SkyboxBlock");
        skyMatrices->set(&sky, sizeof(SkyboxBlock));
        ShaderVariable *tex = _skyShader->variable("skyTexture");
        tex->set(_skyTexture);
        //_skyMesh->draw();
        renderQuad.draw();
        _skyShader->unbind();
    */
    //glClear(GL_DEPTH_BUFFER_BIT);

    updateLight(entities, m);

    auto gameObjects = entities.entities_with_components<TransformComponent, MeshFilterComponent, MaterialComponent>();

    for (auto gameObject : gameObjects)
    {
        auto transform = gameObject.component<TransformComponent>();
        auto meshFilter = gameObject.component<MeshFilterComponent>();
        auto material = gameObject.component<MaterialComponent>();

        Material *currentMaterial = material->material();
        Shader *shader = currentMaterial->shader();
        shader->bind();

        glm::vec3 pos = transform->position();
        glm::vec3 rot = transform->rotation();
        glm::vec3 scl = transform->scale();
        glm::mat4 model = glm::mat4(1.0f);
        applyTransform(model, pos, rot, scl);
        m.model = model;
        m.view = view;

        //For code review: shader updates from one gameObject to another,
        //so, should it be in cycle and should we pass (set) light block in cycle to gpu?
        ShaderBlock *matricies = shader->block("MatrixBlock");
        matricies->set(&m, sizeof(MatrixBlock));

        ShaderBlock *pLightBlock = shader->block("PointLightBlock");
        pLightBlock->set(pointLightBlock);

        ShaderBlock *dLightBlock = shader->block("DirectLightBlock");
        dLightBlock->set(directLightBlock);

        ShaderBlock *sLightBlock = shader->block("SpotLightBlock");
        sLightBlock->set(spotLightBlock);

        meshFilter->mesh()->draw();
        shader->unbind();

        //TODO : make occlusion query (CHC++ ?)
        /*  glm::vec3 *boxScale = reinterpret_cast<glm::vec3 *>(meshFilter->mesh()->scale);
            m.modelView = glm::scale(m.modelView, *boxScale);
            _boxShader->bind();
            ShaderBlock *boxmat = _boxShader->block("MatrixBlock");
            boxmat->set(&m, sizeof(MatrixBlock));
            //_renderer->beginOcclusionQuery();
            _boxMesh->drawBox();
            //bool visible = _renderer->endOcclusionQuery();
            _boxShader->unbind();*/
    }

    _context->swapBuffers();
}

/*  void RenderSystem::geometryPass(std::shared_ptr<EntityManager> entities, MatrixBlock& m)
    {
    _gbuffer.bind(GBuffer::Write);

    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    auto gameObjects = entities->entities_with_components<TransformComponent, MeshFilterComponent, MaterialComponent, RendererComponent>();
    for (auto gameObject : gameObjects)
    {
        auto transform = gameObject.component<TransformComponent>();
        auto meshFilter = gameObject.component<MeshFilterComponent>();
        auto material = gameObject.component<MaterialComponent>();
        auto renderer = gameObject.component<RendererComponent>();

        auto mesh = meshFilter->mesh();

        //glm::mat4 model;
        /*static float angle = 1.0f;
        if (angle == 360) angle = 0;
        lightTransform->setRotation(glm::vec3(0.0f, angle++, 0.0f));*/
//m.model = glm::rotate(m.model, angle++, glm::vec3(0.0f, 1.0f, 0.0f));
/*  glm::mat4 modelView = m.view * m.model;
    m.viewModel = modelView;

    m.normal = glm::transpose(glm::inverse(glm::mat3(modelView)));

    Program *program = material->program();
    program->use();
    UniformBlock matrices = program->block("MatrixBlock");
    //UniformBlock lightb = program->block("Light");
    UniformBlock matb = program->block("Material");
    matrices = m;
    //lightb = lightData;

    struct MaterialData
    {
    glm::vec4 diffuse;
    glm::vec4 ambient;
    glm::vec4 specular;
    glm::float_t shininess;
    glm::float_t __padding[3];
    } matData;

    matData.diffuse = glm::vec4(0.5f, 0.5f, 0.5f, 0.0f);
    matData.ambient = glm::vec4(0.20f, 0.20f, 0.20f, 0.0f);
    matData.specular = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    matData.shininess = 32;

    matb = matData;

    renderer->render();

    //mesh->draw();
    }

    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    }

    void RenderSystem::lightPass(std::shared_ptr<EntityManager> entities, MatrixBlock& m)
    {

    }*/

void RenderSystem::receive(const EntityCreatedEvent& event)
{
    RenderInfo *info = new RenderInfo;
    _renderMap.insert(std::make_pair(event.entity.id(), info));
}

void RenderSystem::receive(const EntityDestroyedEvent& event)
{
    auto info = _renderMap.find(event.entity.id());
    if (info == _renderMap.end())
        return;

    delete info->second;
    _renderMap.erase(info);
}

void RenderSystem::receive(const ComponentAddedEvent<MeshFilterComponent>& event)
{
    //auto info = _renderMap.find(event.entity.id());
    //if (info == _renderMap.end())
    //return;
}

void RenderSystem::receive(const ComponentRemovedEvent<MeshFilterComponent>& event)
{

}

void RenderSystem::chooseBackend(const std::string& name)
{
    //TODO: make choice among renderers available for current platform
    _renderer = new GLRenderer();

    //Create app window with context
    _window = new Window();// _renderer->createWindow();
    _context = new Context();
    _context->makeCurrent(_window);
    GLExt::init(_context);
    //_window->hide();
    //_window->update();
    //_renderer->createOcclusionQuery();
    renderQuad.create();

    /*  _boxShader = _renderer->createShader();
        _boxShader->vertexSource = readFile("resources/shaders/box.vert");
        _boxShader->pixelSource = readFile("resources/shaders/box.frag");
        _boxShader->load();*/

    _skyShader = _renderer->createShader();
    _skyShader->vertexSource = readFile("../src/engine/shaders/skybox.vert");
    _skyShader->pixelSource = readFile("../src/engine/shaders/skybox.frag");
    _skyShader->load();

    TextureResource texResource(_renderer);
    std::ifstream texIn("resources/skybox", std::ios::binary | std::ios::in);
    Object *texObject = nullptr;
    texResource.load(texIn, texObject);
    _skyTexture = static_cast<Texture *>(texObject);
    _skyTexture->load();

    /*  Material *skyMat = new Material();
        skyMat->setShader(_skyShader);
        skyMat->setProperty("skyBox", tex2d);*/

    /*  _boxMesh = _renderer->createMesh();
        _boxMesh->verticies.assign
        ({
        Vertex{ { -0.5, -0.5, -0.5 } },
        Vertex{ { 0.5, -0.5, -0.5 } },
        Vertex{ { 0.5, 0.5, -0.5 } },
        Vertex{ { -0.5, 0.5, -0.5 } },
        Vertex{ { -0.5, -0.5, 0.5 } },
        Vertex{ { 0.5, -0.5, 0.5 } },
        Vertex{ { 0.5, 0.5, 0.5 } },
        Vertex{ { -0.5, 0.5, 0.5 } }
        });
        _boxMesh->indices.assign
        ({
        0, 1, 2, 3,
        4, 5, 6, 7,
        0, 4, 1, 5,
        2, 6, 3, 7
        });
        _boxMesh->load();*/

    /*  float width = 100.0f, height = 100.0f, depth = 100.0f;
        _skyMesh = _renderer->createMesh();
        _skyMesh->verticies.assign
        ({
        Vertex{ { -width, -height, -depth } }, // 0
        Vertex{ { width, -height, -depth } }, // 1
        Vertex{ { width, height, -depth } }, // 2
        Vertex{ { -width, height, -depth } }, // 3
        Vertex{ { -width, -height, depth } }, // 4
        Vertex{ { width, -height, depth } }, // 5
        Vertex{ { width, height, depth } }, // 6
        Vertex{ { -width, height, depth } } // 7
        });
        _skyMesh->indices.assign
        ({
        0, 2, 1,
        0, 3, 2,
        1, 2, 6,
        6, 5, 1,
        4, 5, 6,
        6, 7, 4,
        2, 3, 6,
        6, 3, 7,
        0, 7, 3,
        0, 4, 7,
        0, 1, 5,
        0, 5, 4
        });
        _skyMesh->load();*/
}

Renderer *RenderSystem::renderer() const
{
    return _renderer;
}

Window *RenderSystem::window() const
{
    return _window;
}
