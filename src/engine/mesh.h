#ifndef MESH_H
#define MESH_H

#include "global.h"

#include <vector>
#include <glm/glm.hpp>

class ENGINE_EXPORT Mesh
{
public:
	Mesh();
	virtual ~Mesh();

    std::vector<glm::float_t> positions;
    std::vector<glm::float_t> normals;
    std::vector<glm::float_t> texcoords;
    std::vector<glm::uint> indices;

};

#endif