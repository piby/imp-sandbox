#version 450 core

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec2 i_coord;

uniform mat4 mvpMat;

out vec2 o_coord;

void main()
{
	gl_Position = mvpMat * vec4(i_vertex, 1.0);
	o_coord = vec2(i_coord.x, i_coord.y);
}
