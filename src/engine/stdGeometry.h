#include "mesh.h"
#include "render/renderer.h"

class stdGeometry
{
public:
	stdGeometry(Renderer *currentRenderer = nullptr);
	~stdGeometry();

	Mesh *cube(float length = 1, float width = 1, float height = 1);

private:
	Renderer *m_renderer;
};

