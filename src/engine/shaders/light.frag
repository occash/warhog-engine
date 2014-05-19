#version 430

layout(binding=15) uniform sampler2D albedoTex;
layout(binding=14) uniform sampler2D normalDepthTex;

uniform mat4 InvViewProjection;
uniform vec2 inverseScreenSize;
uniform float farDistance;

layout(std140)
uniform PointLightData
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
	vec3 position;
	float radius;
    vec3 attenuation;
    float intensity;
} light;

layout(std140)
uniform MaterialData
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} material;

in Data
{
	vec4 vertex;
	vec2 coord;
} DataIn;

out vec4 fragColor;

const vec4 globalAmbient = vec4(0.05, 0.05, 0.05, 1.0);

void main()
{
	vec2 texCoord = DataIn.coord;// * inverseScreenSize;
    vec4 nd = texture2D(normalDepthTex, texCoord);
    vec3 normal = nd.xyz;
	float linearDepth = nd.a;

	//vec3 viewRay = vec3(DataIn.vertex.xy * (-farDistance / linearDepth), -farDistance);
    vec4 screenSpacePosition = vec4(DataIn.vertex.xy * 2.0 - 1.0, linearDepth, 1.0);
    vec4 worldSpacePosition = InvViewProjection  * screenSpacePosition;
    vec3 vertex = worldSpacePosition.xyz / worldSpacePosition.w;
    //vec3 vertex = viewRay * linearDepth;

	vec4 ambient = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffuse = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);

	vec3 lightDir = light.position - vertex;
    vec3 R = normalize(reflect(lightDir, normal));
    vec3 V = normalize(vertex);

	float lambert = max(dot(normal, normalize(lightDir)), 0.0);

	if (lambert > 0.0) 
	{
		float distance = length(lightDir);
    
		if (distance <= light.radius)
		{
			float distancePercent = distance / light.radius;
			float damping_factor = 1.0 - pow(distancePercent, 3);
			float attenuation = 1.0 / (light.attenuation.x +
									   light.attenuation.y * distance +
									   light.attenuation.z * distance * distance);
			attenuation *= damping_factor;
      
			vec4 diffuseContribution = material.diffuse * light.diffuse * lambert;
			diffuseContribution *= light.intensity;
			diffuseContribution *= attenuation;
      
			vec4 specularContribution = material.specular * light.specular * pow(max(dot(R, V), 0.0), material.shininess);
			specularContribution *= light.intensity;
			specularContribution *= attenuation;
      
			diffuse += diffuseContribution;
			specular += specularContribution;
		}
	}

	vec4 finalColor = ambient + diffuse + specular;
  
	fragColor = vec4(finalColor.rgb, 1.0);
    //fragColor = vec4(normal, 1.0);
    //fragColor = vec4(linearDepth, linearDepth, linearDepth, 1.0);
}