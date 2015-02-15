#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "../global.h"
#include <entityx/Entity.h>

class CameraComponent;
class LightComponent;
class MaterialComponent;
class MeshFilterComponent;
class TransformComponent;

class ENGINE_EXPORT BaseScript
{
public:
    BaseScript();
    ~BaseScript();

    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}

    CameraComponent *getCamera();
    LightComponent *getLight();
    MaterialComponent *getMaterial();
    MeshFilterComponent *getMeshFilter();
    TransformComponent *getTransform();

public:
    entityx::Entity entity;

protected:
    virtual void proxyObject() const {}

};

class ENGINE_EXPORT ScriptComponent :
    public entityx::Component<ScriptComponent>
{
public:
    ScriptComponent();
    ~ScriptComponent();

    std::vector<BaseScript *> scripts;

};

#endif // SCRIPTCOMPONENT_H
