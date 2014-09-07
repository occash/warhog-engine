#version 440

layout(location=0) in vec3 position;

layout(std140)
uniform MatrixBlock
{
	mat4 modelView;
	mat4 projection;
} mvp;

out Data
{
	vec3 cubeCoord;
} DataOut;

void main()
{
	gl_Position = mvp.projection * mvp.modelView * vec4(position, 1.0);
	DataOut.cubeCoord = vec3(position.x, -position.yz);
}