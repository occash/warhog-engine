#include "glmesh.h"
#include "glextensions.h"

GLMesh::GLMesh()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(0);
}

GLMesh::~GLMesh()
{
	glBindVertexArray(_vao);

	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);

	glBindVertexArray(0);
}

void GLMesh::bind()
{
	glBindVertexArray(_vao);
}

void GLMesh::unbind()
{
	glBindVertexArray(0);
}

void GLMesh::load()
{
	glBindVertexArray(_vao);

	//Bind and load vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_STATIC_DRAW);

	//Bind position attribute (slot 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	//Bind bone weights attribute (slot 1)
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), 
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Bind bone indices attribute (slot 2)
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), 
		(void*)(3 * sizeof(float) + 4 * sizeof(unsigned char)));
	glEnableVertexAttribArray(2);

	//Bind normals attribute (slot 3)
	glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex),
		(void*)(3 * sizeof(float) + 8 * sizeof(unsigned char)));
	glEnableVertexAttribArray(3);

	//Bind texture coordinates attribute (slot 4)
	glVertexAttribPointer(4, 4, GL_HALF_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)(3 * sizeof(float) + 12 * sizeof(unsigned char)));
	glEnableVertexAttribArray(4);

	//Bind tangent attribute (slot 5)
	glVertexAttribPointer(4, 4, GL_HALF_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)(3 * sizeof(float) + 12 * sizeof(unsigned char)));
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GLMesh::unload()
{
	//TODO
}

void GLMesh::draw()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
