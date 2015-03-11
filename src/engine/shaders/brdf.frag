#version 430

layout(std140)
uniform Material
{
    vec3 color;
    float fresnel0;
    float roughness;
} mat;

layout(std140)
uniform DirectLight
{
    vec3 color;
    vec3 direction;
	vec3 intencity;
} light;

in Data 
{
	vec3 position;
	vec3 normal;
} DataIn;

out vec4 fragColor;

//Schlick approximation
float fresnel(float f0, vec3 n, vec3 l)
{
    return f0 + (1.0 - f0) * pow(1.0 - dot(n, l), 5.0);
}

//Beckmann
float distribution(vec3 n, vec3 h, float roughness)
{
    float m_Sq = roughness * roughness;
    float NdotH_Sq = max(dot(n, h), 0.0);
    NdotH_Sq = NdotH_Sq * NdotH_Sq;
    return exp((NdotH_Sq - 1.0) / (m_Sq * NdotH_Sq)) / (3.14159265 * m_Sq * NdotH_Sq * NdotH_Sq);
}

//Cook-Torrance
float geometry(vec3 n, vec3 h, vec3 v, vec3 l, float roughness)
{
    float NdotH = dot(n, h);
    float NdotL = dot(n, l);
    float NdotV = dot(n, v);
    float VdotH = dot(v, h);
    float NdotL_clamped = max(NdotL, 0.0);
    float NdotV_clamped = max(NdotV, 0.0);
    return min(min(2.0 * NdotH * NdotV_clamped / VdotH, 2.0 * NdotH * NdotL_clamped / VdotH), 1.0);
}

//(1 - f0)
float diffuseEnergyRatio(float f0, vec3 n, vec3 l)
{
    return 1.0 - f0;
}

void main()
{
	vec3 normal = normalize(DataIn.normal);
	vec3 view = -normalize(DataIn.position);
	vec3 halfVec = normalize(light.direction + view);
	float NdotL = dot(normal, light.direction);
	float NdotV = dot(normal, view);
	float NdotL_clamped = max(NdotL, 0.0);
	float NdotV_clamped = max(NdotV, 0.0);

	float brdf_spec = fresnel(mat.fresnel0, halfVec, light.direction) *
						geometry(normal, halfVec, view, light.direction, mat.roughness) *
						distribution(normal, halfVec, mat.roughness) /
						(4.0 * NdotL_clamped * NdotV_clamped);
	vec3 color_spec = NdotL_clamped * 
						brdf_spec * 
						light.color  * 
						light.intencity;
	vec3 color_diff = NdotL_clamped * 
					diffuseEnergyRatio(mat.fresnel0, normal, light.direction) * 
					mat.color * 
					light.color;

	fragColor = vec4(color_diff + color_spec
					, 
					1.0);
	//fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}