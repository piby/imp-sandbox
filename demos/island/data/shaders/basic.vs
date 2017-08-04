#version 450 core

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec2 i_coord;

uniform mat4 mvpMat;


out vec3 c_color;

void main()
{
	gl_Position = mvpMat * vec4(i_vertex, 1.0);
	c_color = vec3(i_coord, 1.0);
}
