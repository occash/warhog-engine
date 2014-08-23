#ifndef RENDERERCOMPONENT_H
#define RENDERERCOMPONENT_H

#include "../global.h"

#include <glm/glm.hpp>
#include <entityx/Entity.h>

using namespace entityx;
class Mesh;

class ENGINE_EXPORT RendererComponent : public Component<RendererComponent>
{
public:
	RendererComponent();
	~RendererComponent();

	//void render();
	//void loadData(Mesh *);

private:
	glm::uint _vao; //Array object
    glm::uint _vbo; //Vertex buffer
    glm::uint _nbo; //Normal buffer
    glm::uint _tbo; //Texcoord buffer
    glm::uint _ebo; //Elements buffer
	int _faceNumber;

};

#endif