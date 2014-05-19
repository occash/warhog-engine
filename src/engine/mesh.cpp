#include "mesh.h"


Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}

/*void Mesh::setVertexData(GLfloat *data, GLint size)
{
	if(size <= 0)
		return;

	_verticies = data;
	_vertexSize = size;

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//Load vertex data
	glBufferData(GL_ARRAY_BUFFER, _vertexSize, _verticies, GL_STATIC_DRAW);

	//Bind position attribute (slot 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	//Bind color attribute (slot 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::setElementData(GLuint *data, GLint size)
{
	if(size <= 0)
		return;

	_elements = data;
	_elementSize = size;

	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elementSize, _elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::draw()
{
    if(_vertexSize <= 0)
        return;

	glBindVertexArray(_vao);
    if(_elementSize <= 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glDrawArrays(GL_TRIANGLES, 0, _vertexSize / sizeof(GLuint));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	    glDrawElements(GL_TRIANGLES, _elementSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
	glBindVertexArray(0);
}*/
