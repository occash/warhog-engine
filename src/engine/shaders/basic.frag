#version 430

layout(std140)
uniform Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} material;

in Data
{
	vec3 normal;
	float depth;
} DataIn;

out vec4 outAlbedo;
out vec4 outNormalDepth;

void main()
{
    outAlbedo = material.diffuse;
	outNormalDepth = vec4(normalize(DataIn.normal), DataIn.depth);
}