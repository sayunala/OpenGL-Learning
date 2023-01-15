#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 v_TexCoord;
uniform sampler2D u_Textures[2];

void main(){
	
	
	FragColor = mix(texture(u_Textures[1], v_TexCoord),texture(u_Textures[0],v_TexCoord),0.2);

}