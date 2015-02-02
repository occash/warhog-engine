#version 430

layout(location=0) in vec3 position;

layout(std140)
uniform SkyboxBlock
{
	float fov;
	float width;
	float height;
	mat4 view;
} skybox;

out Data
{
	vec3 viewRay;
} DataOut;

void main()
{
	const vec4 verts[4] = vec4[4](vec4(-1.0, -1.0, 0.5, 1.0),
                                  vec4( 1.0, -1.0, 0.5, 1.0),
                                  vec4(-1.0,  1.0, 0.5, 1.0),
                                  vec4( 1.0,  1.0, 0.5, 1.0));

    gl_Position = verts[gl_VertexID];
	
	DataOut.viewRay = vec3(position.xy * radians(skybox.fov), -1.0);
    DataOut.viewRay.x *= skybox.width / skybox.height;
    DataOut.viewRay = vec3(inverse(skybox.view) * vec4(DataOut.viewRay, 0.0));
}