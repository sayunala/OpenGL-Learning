#version 330 core
out vec4 FragColor;
uniform  vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform vec3 u_Lightpos;//灯光位置
uniform vec3 u_Viewpos;// 眼睛位置
in vec3 v_Normal;//法向量
in vec3 v_Fragpos;

struct Material{
	vec3 ambient;//环境光照下这个表面反射的颜色 
	vec3 diffuse;//漫反射光照下表面颜色 
	vec3 specular;// 表面上镜面高光的颜色

	float shiness;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;
void main(){
	
	float ambienStrength = 0.1;
	vec3 ambient = ambienStrength * u_LightColor;//环境光强


	//计算漫反射光强
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Lightpos - v_Fragpos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_LightColor;

	//计算镜面反射
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_Viewpos - v_Fragpos);
	vec3 reflectDir = reflect(-lightDir, norm);//-lightDir 是因为reflect接受的是lightPos 到 Fragpos的向量
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

	vec3 specular = specularStrength * spec * u_LightColor;
	
	//计算结果
	vec3 result = (diffuse + ambient + specular) * u_ObjectColor;
	FragColor = vec4(result, 1.0f);
}