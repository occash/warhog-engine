#version 430

in vec3 position;
in vec3 normal;

uniform float farDistance;

layout(std140)
uniform MatrixBlock
{
	mat4 modelView;
	mat4 projection;
} mvp;

out Data 
{
	vec3 normal;
	float depth;
} DataOut;

void main()
{
    vec4 eyePos = mvp.modelView * vec4(position, 1.0);
    gl_Position = mvp.projection * eyePos;

	DataOut.depth = -eyePos.z / 99.0;
	DataOut.normal = normalize(vec3(mvp.modelView * vec4(normal, 0.0)));
}