#shader vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 incolor;
layout(location = 3) in float a_TexIndex;

out vec2 v_TexCoord;
out vec4 v_color;
out float v_TexIndex;

uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP*position;
	v_TexCoord = texCoord;
	v_color = incolor;
	v_TexIndex = a_TexIndex;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Textures;

in vec2 v_TexCoord;
in vec4 v_color;
in float v_TexIndex;

void main()
{
	int index = (int)v_TexIndex;
	vec4 texColor = texture(u_Textures, v_TexCoord);
	color = texColor;
};
