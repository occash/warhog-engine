#version 430

in vec3 position;
in vec2 texcoord;

out Data 
{
	vec4 vertex;
	vec2 coord;
} DataOut;

void main()
{
	DataOut.vertex = vec4(position.xy, 0.0, 1.0);
	DataOut.coord = texcoord;
	gl_Position = vec4(position.xy, 0.0, 1.0);
}