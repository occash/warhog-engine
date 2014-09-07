#version 440

uniform samplerCube material_skyBox;

in Data
{
	vec3 cubeCoord;
} DataIn;

layout(location=0) out vec4 fragColor;

void main()
{
	fragColor = texture(material_skyBox, DataIn.cubeCoord);
}