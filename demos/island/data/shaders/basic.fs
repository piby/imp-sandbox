#version 450 core

out vec4 o_color;
in vec3 c_color;

void main()
{
	o_color = vec4(c_color, 1.0);
	//o_color = vec4(1.0, 0.6, 0.6, 1.0);
}

