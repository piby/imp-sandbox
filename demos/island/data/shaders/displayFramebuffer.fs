#version 450 core

out vec4 o_color;
in vec2 o_coord;

layout (location = 0) uniform sampler2D tex;

void main()
{
	o_color = texture(tex, o_coord);
}
