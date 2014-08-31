#include "rendersystem.h"
#include "../components/transformcomponent.h"
#include "../components/cameracomponent.h"
#include "../components/meshfiltercomponent.h"
#include "../components/materialcomponent.h"
#include "../components/renderercomponent.h"
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

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>


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

struct MatrixBlock
{
	glm::mat4 modelView;
	glm::mat4 projection;
};

struct MaterialBlock
{
	glm::vec3 color;
	glm::float_t fresnel0;
	glm::float_t roughness;
	glm::float_t __padding1[3];
};

struct DirectLight
{
	glm::vec3 color;
	glm::float_t __padding0;
	glm::vec3 direction;
	glm::float_t __padding1;
};

RenderSystem::RenderSystem() :
	_renderer(nullptr),
	_window(nullptr)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::configure(EventManager &events)
{
	events.subscribe<EntityCreatedEvent>(*this);
	events.subscribe<EntityDestroyedEvent>(*this);
	events.subscribe<ComponentAddedEvent<MeshFilterComponent>>(*this);
	events.subscribe<ComponentRemovedEvent<MeshFilterComponent>>(*this);
}

void RenderSystem::update(EntityManager &entities, EventManager &events, double dt)
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

    glm::vec3 viewDir = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    viewDir = glm::rotate(viewDir, -camRot.x, glm::vec3(0.0f, 1.0f, 0.0f));
    viewDir = glm::rotate(viewDir, -camRot.y, glm::vec3(1.0f, 0.0f, 0.0f));
    viewDir = glm::rotate(viewDir, -camRot.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(
		camPos,
		camPos + viewDir,
		cameraUp
		);

    m.modelView = view * model;
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

	//Setup lights
    auto lights = entities.entities_with_components<TransformComponent, LightComponent>();
    auto lightObject = lights.begin();

    auto lightTransform = (*lightObject).component<TransformComponent>();
    auto light = (*lightObject).component<LightComponent>();

    glm::vec3 lightDir(1.0f, 0.0f, 0.0f);
    glm::vec3 lightRot = lightTransform->rotation();
    lightDir = glm::rotate(lightDir, -lightRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    lightDir = glm::rotate(lightDir, -lightRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
    lightDir = glm::rotate(lightDir, -lightRot.z, glm::vec3(0.0f, 0.0f, 1.0f));
    lightDir = glm::normalize(lightDir);

    DirectLight dlight;
    dlight.color = glm::vec3(light->color()) * glm::pi<float>();
    glm::vec4 lightDir4 = glm::vec4(lightDir, 1.0f);
    dlight.direction = glm::vec3(lightDir4 * m.modelView);

	//Setup material
	MaterialBlock mat;
	mat.color = glm::vec3(0.9f / glm::pi<float>(),
		0.5f / glm::pi<float>(), 0.55f / glm::pi<float>());
	float refractiveIndex = 16.0f;
	float fresnel0 = ((1.0f - refractiveIndex) / (1.0f + refractiveIndex));
	fresnel0 = fresnel0 * fresnel0;
	mat.fresnel0 = fresnel0;
	mat.roughness = 0.25f;

    auto gameObjects = entities.entities_with_components<TransformComponent, MeshFilterComponent, MaterialComponent>();
    for (auto gameObject : gameObjects)
    {
        auto transform = gameObject.component<TransformComponent>();
        auto meshFilter = gameObject.component<MeshFilterComponent>();
        auto material = gameObject.component<MaterialComponent>();
        auto renderer = gameObject.component<RendererComponent>();

		Material *currentMaterial = material->material();
		Shader *shader = currentMaterial->shader();
		shader->bind();

        ShaderBlock *matricies = shader->block("MatrixBlock");
        matricies->set(&m, sizeof(MatrixBlock));

		ShaderBlock *matblock = shader->block("Material");
        matblock->set(&mat, sizeof(MaterialBlock));

        ShaderBlock *directlight = shader->block("DirectLight");
        directlight->set(&dlight, sizeof(DirectLight));

		meshFilter->mesh()->draw();
    }

	_window->update();
}

/*void RenderSystem::geometryPass(Ptr<EntityManager> entities, MatrixBlock& m)
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
        /*glm::mat4 modelView = m.view * m.model;
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

void RenderSystem::lightPass(Ptr<EntityManager> entities, MatrixBlock& m)
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
	_window = _renderer->createWindow();
	_window->show();
	_window->update();
}

Renderer *RenderSystem::renderer() const
{
	return _renderer;
}
