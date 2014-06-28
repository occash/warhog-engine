#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

//#include <boost/shared_ptr.hpp>
#include "../gbuffer.h"
#include "../window.h"

#include <entityx/System.h>
#include <glm/glm.hpp>


struct MatrixBlock
{
    glm::mat4 modelView;
    glm::mat4 projection;
};

struct Material
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

using namespace entityx;

class RenderSystem : public System<RenderSystem>
{
public:
    RenderSystem(Ptr<Window> window);
    ~RenderSystem();

    void configure(EventManager &events) override;
    void update(EntityManager &entities, EventManager &events, double dt) override;

private:
    Ptr<Window> _window;
    GBuffer _gbuffer;

private:
    void geometryPass(Ptr<EntityManager> entities, MatrixBlock& m_);
    void lightPass(Ptr<EntityManager> entities, MatrixBlock& m);

};

#endif