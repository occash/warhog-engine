#include "uniform.h"
#include "../../program.h"

#include "glextensions.h"
#include <glm/gtc/type_ptr.hpp>

Uniform::Uniform(GLint location)
    : _location(location)
{
}

Uniform::~Uniform()
{
}

void Uniform::operator=(glm::float_t f)
{
    glUniform1f(_location, f);
}

void Uniform::operator=(const glm::vec2& vf)
{
    glUniform2f(_location, vf.x, vf.y);
}

void Uniform::operator=(const glm::vec3& vf)
{
	glUniform3f(_location, vf.x, vf.y, vf.z);
}

void Uniform::operator=(const glm::vec4& vf)
{
    glUniform4f(_location, vf.x, vf.y, vf.z, vf.w);
}

void Uniform::operator=(glm::int_t i)
{
    glUniform1i(_location, i);
}

void Uniform::operator=(const glm::ivec2& vi)
{
    glUniform2i(_location, vi.x, vi.y);
}

void Uniform::operator=(const glm::ivec3& vi)
{
    glUniform3i(_location, vi.x, vi.y, vi.z);
}

void Uniform::operator=(const glm::ivec4& vi)
{
    glUniform4i(_location, vi.x, vi.y, vi.z, vi.w);
}

void Uniform::operator=(glm::uint_t u)
{
    glUniform1ui(_location, u);
}

void Uniform::operator=(const glm::uvec2& vu)
{
    glUniform2ui(_location, vu.x, vu.y);
}

void Uniform::operator=(const glm::uvec3& vu)
{
    glUniform3ui(_location, vu.x, vu.y, vu.z);
}

void Uniform::operator=(const glm::uvec4& vu)
{
    glUniform4ui(_location, vu.x, vu.y, vu.z, vu.w);
}

void Uniform::operator=(bool b)
{
    glUniform1ui(_location, b);
}

void Uniform::operator=(const glm::bvec2& vb)
{
    glUniform2ui(_location, vb.x, vb.y);
}

void Uniform::operator=(const glm::bvec3& vb)
{
    glUniform3ui(_location, vb.x, vb.y, vb.z);
}

void Uniform::operator=(const glm::bvec4& vb)
{
    glUniform4ui(_location, vb.x, vb.y, vb.z, vb.w);
}

void Uniform::operator=(const glm::mat2& m)
{
    glUniformMatrix2fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat2x3& m)
{
    glUniformMatrix2x3fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat2x4& m)
{
    glUniformMatrix2x4fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat3& m)
{
    glUniformMatrix3fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat3x2& m)
{
    glUniformMatrix3x2fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat3x4& m)
{
    glUniformMatrix3x4fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat4& m)
{
    glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat4x2& m)
{
    glUniformMatrix4x2fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}

void Uniform::operator=(const glm::mat4x3& m)
{
    glUniformMatrix4x3fv(_location, 1, GL_FALSE, glm::value_ptr(m));
}
