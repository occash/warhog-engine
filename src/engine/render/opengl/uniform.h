#ifndef UNIFORM_H
#define UNIFORM_H

#include <glm/glm.hpp>

class Uniform
{
public:
	Uniform(glm::int_t location);
	virtual ~Uniform();

    void operator=(glm::float_t f);
    void operator=(const glm::vec2& vf);
	void operator=(const glm::vec3& vf);
    void operator=(const glm::vec4& vf);

    void operator=(glm::int_t i);
    void operator=(const glm::ivec2& vi);
    void operator=(const glm::ivec3& vi);
    void operator=(const glm::ivec4& vi);

    void operator=(glm::uint_t u);
    void operator=(const glm::uvec2& vu);
    void operator=(const glm::uvec3& vu);
    void operator=(const glm::uvec4& vu);

    void operator=(bool b);
    void operator=(const glm::bvec2& vb);
    void operator=(const glm::bvec3& vb);
    void operator=(const glm::bvec4& vb);

    void operator=(const glm::mat2& m);
    void operator=(const glm::mat2x3& m);
    void operator=(const glm::mat2x4& m);
    void operator=(const glm::mat3& m);
    void operator=(const glm::mat3x2& m);
    void operator=(const glm::mat3x4& m);
    void operator=(const glm::mat4& m);
    void operator=(const glm::mat4x2& m);
    void operator=(const glm::mat4x3& m);

private:
	glm::int_t _location;
    
};

#endif