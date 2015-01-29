#version 430

uniform samplerCube skyTexture;
const float bright = 1.0;

in Data
{
	vec3 viewRay;
} DataIn;

layout(location=0) out vec4 fragColor;

void main()
{
	fragColor = vec4(texture(skyTexture, DataIn.viewRay).rgb, 1.0);
}