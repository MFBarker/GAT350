#version 430 core 

in layout(location = 0) vec3 vposition; // 0
in layout(location = 1) vec3 vcolor; // 1
in layout(location = 2) vec2 vtextcoords; // 2

out vec3 color;
out vec2 textcoords;

uniform float scale;
uniform mat4 mvp;

void main()
{
	color = vcolor;

	textcoords = vtextcoords;

	gl_Position = mvp * vec4(vposition * scale, 1.0);

	//gl_Position = tposition;//vec4(vposition * scale, 1.0);
}
