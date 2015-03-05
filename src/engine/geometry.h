#include "mesh.h"

class Renderer;

class Geometry
{
public:
    Geometry(Renderer *currentRenderer = nullptr);
    ~Geometry();

	Mesh *cube(float width = 1, float height = 1, float depth = 1, 
		int widthDiv = 1, int heightDiv = 1, int depthDiv = 1);

    Mesh *plane(float width = 1, float height = 1);

private:
    Renderer *m_renderer;
};

