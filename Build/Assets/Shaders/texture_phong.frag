#version 430 core
 
in vec3 position;
in vec3 normal;
in vec2 texcoord;
 
out vec4 fcolor;

struct Light
{
	vec3 ambient;
	vec3 color;
	vec4 position;
};

struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
};
 
uniform Light light;
uniform Material material;
uniform sampler2D texture1;
 
void main()
{
	//AMBIENT
	vec3 ambient = light.ambient * material.color;
	
	//DIFFUSE
	//calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3(light.position) - position);

	//calculate light intensity w/ dot product (normal * light direction)
	float intensity = max(dot(light_dir,normal), 0);
	//calculate diffuse color
	vec3 diffuse = light.color * material.color * intensity;

	//  SPECULAR
	vec3 specular = vec3(0);
	if(intensity > 0)
	{
		vec3 reflection = reflect(-light_dir,normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection,view_dir), 0);

		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}
	vec2 ttexcoord = (texcoord * material.uv_tiling + material.uv_offset);

	//fcolor
	fcolor = vec4(ambient + diffuse, 1) * texture(texture1, ttexcoord) + vec4(specular, 1);

}