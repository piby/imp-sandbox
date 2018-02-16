#version 450 core

out vec4 o_color;
in vec2 o_coord;

layout (location = 0) uniform sampler2D tex;
//layout (location = 0) uniform sampler2DMS tex;

void main()
{
	o_color = texture(tex, o_coord);
	//o_color = texelFetch(tex, ivec2(gl_FragCoord.xy), gl_SampleID);
}
