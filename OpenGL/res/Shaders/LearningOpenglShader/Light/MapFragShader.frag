#version 330 core
out vec4 FragColor;
//uniform  vec3 u_ObjectColor;
//uniform vec3 u_LightColor;

uniform vec3 u_Lightpos;//灯光位置
uniform vec3 u_Viewpos;// 眼睛位置
in vec3 v_Normal;//法向量
in vec3 v_Fragpos;//像素的世界位置计算光线的
in vec2 v_TexCoords;// 贴图坐标


struct Material{
	sampler2D diffuse;//漫反射光照下表面颜色 
	sampler2D specular;// 表面上镜面高光的颜色
	sampler2D emission;
	float shinines;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;
uniform float u_Matrixlight;
uniform float u_Matrixmove;

void main(){
	
	float ambienStrength = 0.1;
	vec3 ambient =  u_Light.ambient;//环境光强

	//计算漫反射光强
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_Fragpos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_Light.diffuse;

	//计算镜面反射
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_Viewpos - v_Fragpos);
	vec3 reflectDir = reflect(-lightDir, norm);//-lightDir 是因为reflect接受的是lightPos 到 Fragpos的向量
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shinines);

	vec3 specular =  spec * u_Light.specular;

	vec3 emission = u_Matrixlight*texture(u_Material.emission, v_TexCoords + vec2(0.0, u_Matrixmove)).rgb;
	//计算结果
	vec3 result = diffuse * vec3(texture(u_Material.diffuse, v_TexCoords)) + 
				ambient * vec3(texture(u_Material.diffuse, v_TexCoords)) + 
				specular * vec3(texture(u_Material.specular, v_TexCoords)) + emission;
	FragColor = vec4(result, 1.0f);
}