#version 430 core 
 
in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
 
out vec2 texcoord;
out vec3 color;

struct Light
{
	vec3 color;
	vec4 position;
};

struct Material
{
	vec3 color;
	float shininess;
};
 
uniform Light light;
uniform Material material;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
void main()
{
	texcoord = vtexcoord;

	//  DIFFUSE
	//create model view matrix
	mat4 model_view = view * model;
	//transform normals to viewspace
	vec3 normal = mat3(model_view) * vnormal;
	//transforms positions to view space
	vec4 position = model_view * vec4(vposition, 1);
	//calculate light direction (unit vector)
	vec3 light_dir = vec3(light.position - position);

	//calculate light intensity w/ dot product (normal * light direction)
	float intensity = max(dot(light_dir,vnormal), 0);
	vec3 diffuse = light.color * intensity;

	//  SPECULAR
	vec3 specular = vec3(0);
	if(intensity > 0)
	{
		vec3 reflection = reflect(-light_dir,normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection,view_dir), 0);

		intensity = pow(intensity, 32.0); //32 is temp for material
		specular = light.color * intensity;
	}

	color = vec3(0.5) +  diffuse + specular;
 
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}