#include "renderercomponent.h"
#include "../mesh.h"

#include "../render/opengl/glextensions.h"

RendererComponent::RendererComponent()
	: _faceNumber(0)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	//Dirty hack
	glGenBuffers(4, &_vbo);

	glBindVertexArray(0);
}


RendererComponent::~RendererComponent()
{
}

/*void RendererComponent::loadData(Mesh *mesh)
{
	glBindVertexArray(_vao);

	//Bind and load vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->positions.size() * sizeof(glm::float_t), mesh->positions.data(), GL_STATIC_DRAW);
	//Bind position attribute (slot 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//Bind and load normal buffer
	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(GLfloat), mesh->normals.data(), GL_STATIC_DRAW);
	//Bind normal attribute (slot 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//Bind and load texcoord buffer
	glBindBuffer(GL_ARRAY_BUFFER, _tbo);
	glBufferData(GL_ARRAY_BUFFER, m.texcoords.size() * sizeof(GLfloat), m.texcoords.data(), GL_STATIC_DRAW);
	//Bind texcoord attribute (slot 2)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(glm::uint), mesh->indices.data(), GL_STATIC_DRAW);
    _faceNumber = mesh->indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RendererComponent::render()
{
	glBindVertexArray(_vao);
	if (_elementSize <= 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glDrawArrays(GL_TRIANGLES, 0, _vertexSize / sizeof(GLuint));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glDrawElements(GL_TRIANGLES, _faceNumber, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}*/