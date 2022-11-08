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

layout (binding = 0) uniform sampler2D diffuseMap;//diffuse map
layout (binding = 1) uniform sampler2D specularMap;//specular map
layout (binding = 2) uniform sampler2D emissiveMap;//emissive map

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	//AMBIENT
	ambient = light.ambient * material.color;
	
	//DIFFUSE
	//calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3(light.position) - position);

	//calculate light intensity w/ dot product (normal * light direction)
	float intensity = max(dot(light_dir,normal), 0);
	//calculate diffuse color
	diffuse = light.color * material.color * intensity;

	//  SPECULAR
	specular = vec3(0);
	if(intensity > 0)
	{
		vec3 reflection = reflect(-light_dir,normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection,view_dir), 0);

		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}
}
 
void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	phong(position, normal, ambient, diffuse, specular);
	
	vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;

	vec4 texture_color = texture(diffuseMap, ttexcoord);
	//vec4 texture_color = mix(texture(diffuseMap, ttexcoord), texture(specularMap, ttexcoord),0.5);

	//fcolor
	fcolor = texture(emissiveMap,ttexcoord) + vec4(ambient + diffuse, 1) * texture_color + vec4(specular, 1) * texture(specularMap,ttexcoord);

}
