#version 430 core

in layout (location = 0) vec3 vposition;

out vec3 textcoord;

uniform mat4 model;
uniform mat4 view;

void main()
{
	textcoord = vpositon;

	mat4 vp = projection * mat4(mat3(view));
	gl_position = vp * vec4(vposition,1.0);
}