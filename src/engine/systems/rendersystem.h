#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../components/meshfiltercomponent.h"
#include "../render/renderer.h"
#include "../window.h"

#include <entityx/System.h>
#include <map>

using namespace entityx;
struct RenderInfo;

class RenderSystem : public System<RenderSystem>, public Receiver<RenderSystem>
{
public:
    RenderSystem();
    ~RenderSystem();

	void chooseBackend(const std::string& name);
	Renderer *renderer() const;

    void configure(EventManager &events) override;
    void update(EntityManager &entities, EventManager &events, double dt) override;

	void receive(const EntityCreatedEvent& event);
	void receive(const EntityDestroyedEvent& event);
	void receive(const ComponentAddedEvent<MeshFilterComponent>& event);
	void receive(const ComponentRemovedEvent<MeshFilterComponent>& event);

private:
	typedef std::map<Entity::Id, RenderInfo*> RenderMap;
	Renderer *_renderer;
    Window *_window;
	RenderMap _renderMap;

};

#endif