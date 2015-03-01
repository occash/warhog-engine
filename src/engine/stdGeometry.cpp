#include "stdGeometry.h"


stdGeometry::stdGeometry(Renderer *currentRenderer) : m_renderer(currentRenderer)
{
}


stdGeometry::~stdGeometry()
{
}

Mesh *stdGeometry::cube(float length, float width, float height)
{
	Mesh *m_cube = m_renderer->createMesh();

	std::vector<Vertex> verticies;

	Vertex h_vertex;

	h_vertex.position[0] = -1;
	h_vertex.normal[0] = -1;
	h_vertex.position[1] = -1;
	h_vertex.normal[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	//////////////////2///////////////////////

	h_vertex.position[0] = -1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	////////////////////////3//////////////////////////

	h_vertex.position[0] = -1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	////////////////////////4//////////////////////////

	h_vertex.position[0] = -1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	////////////////////////5//////////////////////////

	h_vertex.position[0] = 1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = 1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = 1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	////////////////////////6//////////////////////////

	h_vertex.position[0] = -1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = -1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = -1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = 1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = 1;
	verticies.push_back(h_vertex);

	h_vertex.position[0] = -1;
	h_vertex.position[1] = 1;
	h_vertex.position[2] = -1;
	h_vertex.normal[0] = -1;
	h_vertex.normal[1] = 1;
	h_vertex.normal[2] = -1;
	verticies.push_back(h_vertex);

	

	for (int i = 0; i < m_cube->verticies.size(); ++i)
	{
		//m_cube->verticies[i].position[3] -= 4;


		for (int j = 0; j < 3; ++j)
		{
			m_cube->verticies[i].normal[j] = -m_cube->verticies[i].position[j];
		}
	}
	m_cube->verticies = verticies;
	m_cube->indices = { 

		0, 1, 2, 0, 2, 3,    // front
		4, 5, 6, 4, 6, 7,    // back
		8, 9, 10, 8, 10, 11,   // top
		12, 13, 14, 12, 14, 15,   // bottom
		16, 17, 18, 16, 18, 19,   // right
		20, 21, 22, 20, 22, 23    // left
	};

	return m_cube;
}
