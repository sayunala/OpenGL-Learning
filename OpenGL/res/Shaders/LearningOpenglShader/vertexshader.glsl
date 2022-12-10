#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_TexCoord;
uniform mat4 u_MVP;
out vec4 vertexColor;
out vec2 v_TexCoord;
void main(){

	gl_Position = u_MVP*vec4(position, 1.0f);
	vertexColor = vec4(position, 1.0f);
	v_TexCoord = a_TexCoord;
}