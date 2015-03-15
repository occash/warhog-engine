#version 430

in vec3 position;
//in vec4 boneweights;
//in vec4 boneindicies;
in vec4 normal;
//in vec2 uv;
//in vec4 tangent;

out Data 
{
	vec3 position;			// camera space
	vec3 normal;			// camera space
	vec3 eyeDirection;		// camera space
	vec3 lightDirection;	// camera space
} DataOut;

layout(std140)
uniform PointLight
{
	vec4 position;
    vec3 color;
    vec3 intensity;
} pLight;


layout(std140)
uniform MatrixBlock
{
	mat4 model;
	mat4 view;
	mat4 projection;
} mvp;

vec4 unpack(vec4 n)
{
	float x = n.x * 2.0 - 1;
	float y = n.y * 2.0 - 1;
	float z = n.z * 2.0 - 1;
	float w = n.w * 2.0 - 1;
	vec4 nres = vec4(x, y, z, w);
	return nres;
}

/*void main()
{
	mat4 normalMatrix = transpose((mvp.view * mvp.model));
    vec4 eyePos = mvp.view * mvp.model * vec4(position, 1.0);
	DataOut.position = vec3(eyePos);
	DataOut.normal = vec3(normalMatrix * unpack(normal));
	gl_Position = mvp.projection * eyePos;
}*/

void main()
{
	gl_Position = mvp.projection * mvp.view * mvp.model * vec4(position, 1.0);

	DataOut.position = (mvp.view * mvp.model * vec4(position, 1)).xyz;
	DataOut.eyeDirection = vec3(0,0,0) - DataOut.position;

	vec3 lightPositionCameraSpace = (mvp.view * pLight.position).xyz;
	DataOut.lightDirection = lightPositionCameraSpace + DataOut.eyeDirection;

	DataOut.normal = (mvp.view * mvp.model * unpack(normal)).xyz;
}
