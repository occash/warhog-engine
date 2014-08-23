#version 430

in vec3 position;
in vec4 boneweights;
in vec4 boneindicies;
in vec4 normal;
in vec2 uv;
in vec4 tangent;

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
	DataOut.normal = vec3(mvp.modelView * normal);
	gl_Position = mvp.projection * eyePos;
}