#version 430

layout(location=0) in vec3 position;

layout(std140)
uniform MatrixBlock
{
	mat4 modelView;
	mat4 projection;
} mvp;

void main()
{
	gl_Position = mvp.projection * mvp.modelView * vec4(position, 1.0);
}