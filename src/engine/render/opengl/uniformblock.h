#ifndef UNIFORMBLOCK_H
#define UNIFORMBLOCK_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../meta/any.h"

class UniformBlock
{
public:
    UniformBlock(glm::uint programm, glm::int_t location);
    UniformBlock(const UniformBlock& other);
    ~UniformBlock();

    template <class T>
    void operator=(const T& value);

	void set(const char *name, const Any& value);

private:
    void loadData(int size, void *value);

private:
    static glm::uint _globalBind;

    glm::uint _buffer;
    glm::int_t _size;

};

template <class T>
void UniformBlock::operator=(const T& value)
{
    loadData(sizeof(value), (void *)&value);
}

#endif
