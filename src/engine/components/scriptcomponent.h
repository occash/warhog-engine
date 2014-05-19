#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "../global.h"

#include <entityx/Entity.h>

using namespace entityx;

class CameraComponent;
class LightComponent;
class MaterialComponent;
class MeshFilterComponent;
class RendererComponent;
class TransformComponent;

class ENGINE_EXPORT ScriptComponent : public Component<ScriptComponent>
{
public:
    ScriptComponent();
    ~ScriptComponent();

    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}

    static Family maxComponents();

    CameraComponent *getCamera();
    LightComponent *getLight();
    MaterialComponent *getMaterial();
    MeshFilterComponent *getMeshFilter();
    RendererComponent *getRenderer();
    TransformComponent *getTransform();

public:
    Entity entity;

    virtual void proxyObject() const {}

private:
    static Family _family;

};

#endif // SCRIPTCOMPONENT_H
