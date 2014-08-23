#include "uniformblock.h"

#include "glextensions.h"
#include <memory.h>
#include <iostream>


UniformBlock::UniformBlock(glm::uint programm, glm::int_t location)
{
    glm::uint bind = ++_globalBind;
    //Create new binding
    glUniformBlockBinding(programm, location, bind);
    glGetActiveUniformBlockiv(programm, location, GL_UNIFORM_BLOCK_DATA_SIZE, &_size);

    //Generate buffer for block
    glGenBuffers(1, &_buffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bind, _buffer);
}

UniformBlock::UniformBlock(const UniformBlock& other)
    : _buffer(other._buffer),
    _size(other._size)
{
}

UniformBlock::~UniformBlock()
{
    //glDeleteBuffers(1, &_buffer);
    //_globalBind--;
}

void UniformBlock::loadData(int size, void *value)
{
    if(size != _size)
    {
        std::cout << "Block size not equal to data size";
        return;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
    glBufferData(GL_UNIFORM_BUFFER, size,
        value, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlock::set(const char *name, const Any& value)
{

}

glm::uint UniformBlock::_globalBind = 0;
