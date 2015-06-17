#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../components/meshfiltercomponent.h"
#include "../render/renderer.h"
#include "../window.h"
#include "../context.h"
#include "../lightinterface.h"
#include "../components/lightcomponent.h"

#include <entityx/System.h>
#include <map>

struct RenderInfo;
class Shader;
class Mesh;

class RenderSystem : public entityx::System<RenderSystem>,
    public entityx::Receiver<RenderSystem>
{
public:
    RenderSystem();
    ~RenderSystem();

    void chooseBackend(const std::string& name);
    Renderer *renderer() const;
    Window *window() const;

    void configure(entityx::EventManager& events) override;
    void update(entityx::EntityManager& entities,
                entityx::EventManager& events, double dt) override;

    void receive(const entityx::EntityCreatedEvent& event);
    void receive(const entityx::EntityDestroyedEvent& event);
    void receive(const entityx::ComponentAddedEvent<MeshFilterComponent>& event);
    void receive(const entityx::ComponentRemovedEvent<MeshFilterComponent>& event);


	void changeLightType(){ ; }

	void* getStucture(LightType lightType);
	LightInterface* getNewInterface(LightType lightType = Directional);

private:
    void renderSkyBox();

private:
    typedef std::map<entityx::Entity::Id, RenderInfo *> RenderMap;
    Renderer *_renderer;
    Window *_window;
    Context *_context;
    RenderMap _renderMap;
    Shader *_boxShader;
    Shader *_skyShader;
    Mesh *_boxMesh;
    Mesh *_skyMesh;
    Texture *_skyTexture;

	DirectLight directLightBlock[64];
	PointLight pointLightBlock[64];
	SpotLight spotLightBlock[64];

	int pointLightInd = 0;
	int spotLightInd = 0;
	int directLightInd = 0;
};

#endif