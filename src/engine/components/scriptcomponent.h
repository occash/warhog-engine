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
	RendererComponent *getRenderer();
	TransformComponent *getTransform();

public:
	Entity entity;

protected:
	virtual void proxyObject() const {}

};

class ENGINE_EXPORT ScriptComponent : public Component<ScriptComponent>
{
public:
    ScriptComponent();
    ~ScriptComponent();

	std::vector<BaseScript *> scripts;

};

#endif // SCRIPTCOMPONENT_H
