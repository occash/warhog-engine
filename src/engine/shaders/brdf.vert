#version 430

in vec3 position;
in vec3 normal;

layout(std140)
uniform MatrixBlock
{
	mat4 modelView;
	mat4 projection;
} mvp;

out Data 
{
	vec3 position;
	vec3 normal;
} DataOut;

void main()
{
    vec4 eyePos = mvp.modelView * vec4(position, 1.0);
	DataOut.position = vec3(eyePos);
	DataOut.normal = vec3(mvp.modelView * vec4(normal, 0.0));
	gl_Position = mvp.projection * eyePos;
}