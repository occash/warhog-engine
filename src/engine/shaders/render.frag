#version 430

layout(binding=15) uniform sampler2D albedoTex;
layout(binding=13) uniform sampler2D lightTex;

in Data
{
	vec2 coord;
} DataIn;

out vec4 fragColor;

void main()
{
	vec4 albedo = texture2D(albedoTex, DataIn.coord);
	vec4 lightContribution = texture2D(lightTex, DataIn.coord);

	vec4 finalColor = lightContribution * albedo;
	fragColor = finalColor;

	/*vec2 dx = vec2 (1.0 / textureSize(albedoTex, 0).x, 0.0);
    vec2 dy = vec2 (0.0, 1.0 / textureSize(albedoTex, 0).y);
    vec4 albedo = texture2D (albedoTex, coord) +
                texture2D (albedoTex, coord + dx) +
                texture2D (albedoTex, coord + dy) +
                texture2D (albedoTex, coord + dx + dy);

    albedo *= 0.25;

    if (length (albedo.rgb) < 0.8)
        albedo.rgb = vec3 (0.0);*/

	/*vec2 tx  = coord;
    vec2 dx  = vec2 (0.001953,0.000000);
    vec2 sdx = dx;
    vec4 sum = texture2D ( albedoTex, tx ) * 0.134598;

    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.127325;
    sdx += dx;
    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.107778;
    sdx += dx;
    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.081638;
    sdx += dx;
    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.055335;
    sdx += dx;
    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.033562;
    sdx += dx;
    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.018216;
    sdx += dx;
    sum += (texture2D ( albedoTex, tx + sdx ) + texture2D ( albedoTex, tx - sdx ) )* 0.008847;
    sdx += dx;*/

	//fragColor = albedo;//vec4(sum.rgb / 1.5, 1.0);
}