#include "scriptcomponent.h"
#include "cameracomponent.h"
#include "lightcomponent.h"
#include "materialcomponent.h"
#include "meshfiltercomponent.h"
#include "transformcomponent.h"


BaseScript::BaseScript()
{

}

BaseScript::~BaseScript()
{

}

CameraComponent *BaseScript::getCamera()
{
    return entity.component<CameraComponent>().get();
}

LightComponent *BaseScript::getLight()
{
    return entity.component<LightComponent>().get();
}

MaterialComponent *BaseScript::getMaterial()
{
    return entity.component<MaterialComponent>().get();
}

MeshFilterComponent *BaseScript::getMeshFilter()
{
    return entity.component<MeshFilterComponent>().get();
}

TransformComponent *BaseScript::getTransform()
{
    return entity.component<TransformComponent>().get();
}

ScriptComponent::ScriptComponent()
{
}

ScriptComponent::~ScriptComponent()
{
}
