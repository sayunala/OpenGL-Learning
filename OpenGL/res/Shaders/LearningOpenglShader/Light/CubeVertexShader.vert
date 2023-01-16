#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 a_normal;
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;
out vec3 v_Fragpos;
void main(){

	gl_Position = u_MVP*vec4(position, 1.0f);
	v_Fragpos = vec3(u_Model * vec4(position, 1.0f));
	//transpose(inverse(u_Model)) ∑®œﬂæÿ’Û
	v_Normal = mat3(transpose(inverse(u_Model))) * a_normal;

}