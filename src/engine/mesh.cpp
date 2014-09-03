#include "mesh.h"


Mesh::Mesh()
{
	scale[0] = 1.0f;
	scale[1] = 1.0f;
	scale[2] = 1.0f;

	delta[0] = 0.0f;
	delta[1] = 0.0f;
	delta[2] = 0.0f;
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
}

void Mesh::unbind()
{
}

void Mesh::load()
{
}

void Mesh::unload()
{
}

void Mesh::draw()
{
}

void Mesh::createBox()
{
	float minbox[3]
	{
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max()
	};
	float maxbox[3]
	{
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min()
	};

	for (int i = 0; i < verticies.size(); ++i)
	{
		if (verticies[i].position[0] < minbox[0]) minbox[0] = verticies[i].position[0];
		if (verticies[i].position[1] < minbox[1]) minbox[1] = verticies[i].position[1];
		if (verticies[i].position[2] < minbox[2]) minbox[2] = verticies[i].position[2];

		if (verticies[i].position[0] > maxbox[0]) maxbox[0] = verticies[i].position[0];
		if (verticies[i].position[1] > maxbox[1]) maxbox[1] = verticies[i].position[1];
		if (verticies[i].position[2] > maxbox[2]) maxbox[2] = verticies[i].position[2];
	}

	scale[0] = maxbox[0] - minbox[0];
	scale[1] = maxbox[1] - minbox[1];
	scale[2] = maxbox[2] - minbox[2];

	delta[0] = minbox[0] + scale[0] / 2;
	delta[1] = minbox[1] + scale[1] / 2;
	delta[2] = minbox[2] + scale[2] / 2;
}

void Mesh::drawBox()
{

}
