#version 430

in Data 
{
	vec3 position;			// camera space
	vec3 normal;			// camera space
} DataIn;

out vec4 fragColor;

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
    vec3 intensity;
} light;

layout(std140)
uniform PointLight
{
	vec4 position;
    vec3 color;
	float power;

} pLight;

uniform MatrixBlock
{
	mat4 model;
	mat4 view;
	mat4 projection;
} mvp;
//Schlick approximation
float fresnel(float f0, vec3 h, vec3 l)
{
    return f0 + (1.0 - f0) * pow(1.0 - dot(h, l), 5.0);
}



//Beckmann
float distribution(vec3 n, vec3 h, float roughness)
{
    float m_Sq = roughness * roughness;
    float NdotH_Sq = max(dot(n, h), 0.0);
    NdotH_Sq = NdotH_Sq * NdotH_Sq;
    return exp((NdotH_Sq - 1.0) / (m_Sq * NdotH_Sq)) / 
			(3.14159265 * m_Sq * NdotH_Sq * NdotH_Sq);
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
    return 1.0 - f0;//(1.0 - (f0  + (1 - f0) * pow(dot(n, l), 5)));
}

vec3 ads()
{
	vec3 n = normalize(DataIn.normal);
	vec3 s = normalize(vec3(pLight.position) - DataIn.position);
	vec3 v = normalize(-DataIn.position);
	vec3 h = normalize(v + s);

	return pLight.color *
			(0.03 +
			0.1 * max(dot(s, DataIn.normal), 0.0) +
			0.5 * pow(max(dot(h,n), 0.0), 3));
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

    float brdf_spec = 0;/*fresnel(mat.fresnel0, halfVec, light.direction) *
						geometry(normal, halfVec, view, light.direction, mat.roughness) *
						distribution(normal, halfVec, mat.roughness) /
						(4.0 * NdotL_clamped * NdotV_clamped);*/
    vec3 color_spec = vec3(0.0f, 0.0f, 0.0f);/*NdotL_clamped * 
						brdf_spec * 
						light.color  * 
						light.intensity;*/
    vec3 color_diff = vec3(0.0f, 0.0f, 0.0f);/*NdotL_clamped * 
					diffuseEnergyRatio(mat.fresnel0, normal, light.direction) * 
					mat.color * 
					light.color;*/


    /////fragment with point light ////////
	
	vec3 s = normalize(vec3(pLight.position) - DataIn.position);
    halfVec = normalize(s + view);
    NdotL = dot(normal, s);
    NdotV = dot(normal, view);
    NdotL_clamped = max(NdotL, 0.0);
    NdotV_clamped = max(NdotV, 0.0);

	float dist = length(vec3(pLight.position) - DataIn.position);
	dist = dist * dist;

    brdf_spec = fresnel(mat.fresnel0, halfVec, s) *
						geometry(normal, halfVec, view, s, mat.roughness) *
						distribution(normal, halfVec, mat.roughness) /
						(4.0 * NdotL_clamped * NdotV_clamped);
    color_spec += pLight.power * NdotL_clamped * 
						brdf_spec * 
						pLight.color /
						dist;

    color_diff += pLight.power * NdotL_clamped * 
					diffuseEnergyRatio(mat.fresnel0, normal, s) * 
					mat.color * pLight.color / dist;

	//////////////////////////////////////////////

	//fragColor = vec4(ads(), 1.0);

    fragColor = vec4(color_diff + color_spec
					, 
					1.0);
    //fragColor = vec4(normal, 1.0);
	//fragColor = vec4(s, 1.0);
	//fragColor = vec4(NdotL_clamped, 0.0, 0.0, 1.0);
}
