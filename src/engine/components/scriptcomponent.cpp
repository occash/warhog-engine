#include "scriptcomponent.h"
#include "cameracomponent.h"
#include "lightcomponent.h"
#include "materialcomponent.h"
#include "meshfiltercomponent.h"
#include "renderercomponent.h"
#include "transformcomponent.h"

ScriptComponent::ScriptComponent()
{
}


ScriptComponent::~ScriptComponent()
{
}

BaseComponent::Family ScriptComponent::maxComponents()
{
    return family_counter_;
}

CameraComponent * ScriptComponent::getCamera()
{
    return entity.component<CameraComponent>().get();
}

LightComponent * ScriptComponent::getLight()
{
    return entity.component<LightComponent>().get();
}

MaterialComponent * ScriptComponent::getMaterial()
{
    return entity.component<MaterialComponent>().get();
}

MeshFilterComponent * ScriptComponent::getMeshFilter()
{
    return entity.component<MeshFilterComponent>().get();
}

RendererComponent * ScriptComponent::getRenderer()
{
    return entity.component<RendererComponent>().get();
}

TransformComponent * ScriptComponent::getTransform()
{
    return entity.component<TransformComponent>().get();
}

BaseComponent::Family ScriptComponent::_family;
