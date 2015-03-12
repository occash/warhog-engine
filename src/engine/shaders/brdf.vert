#version 430

in vec3 position;
//in vec4 boneweights;
//in vec4 boneindicies;
in vec4 normal;
//in vec2 uv;
//in vec4 tangent;

out Data 
{
	vec3 position;
	vec3 normal;
} DataOut;

layout(std140)
uniform MatrixBlock
{
	mat4 model;
	mat4 view;
	mat4 projection;
} mvp;

vec4 unpack(vec4 n)
{
	float x = n.x * 2.0 - 1;
	float y = n.y * 2.0 - 1;
	float z = n.z * 2.0 - 1;
	float w = n.w * 2.0 - 1;
	vec4 nres = vec4(x, y, z, w);
	return nres;
}

void main()
{
    vec4 eyePos = mvp.view * mvp.model * vec4(position, 1.0);
	DataOut.position = vec3(eyePos);
	DataOut.normal = vec3(mvp.model * unpack(normal));
	gl_Position = mvp.projection * eyePos;
}