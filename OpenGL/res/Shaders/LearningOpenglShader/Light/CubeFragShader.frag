#version 330 core
out vec4 FragColor;
uniform  vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform vec3 u_Lightpos;//�ƹ�λ��
uniform vec3 u_Viewpos;// �۾�λ��
in vec3 v_Normal;//������
in vec3 v_Fragpos;

struct Material{
	vec3 ambient;//����������������淴�����ɫ 
	vec3 diffuse;//����������±�����ɫ 
	vec3 specular;// �����Ͼ���߹����ɫ

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
	vec3 ambient = ambienStrength * u_LightColor;//������ǿ


	//�����������ǿ
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Lightpos - v_Fragpos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_LightColor;

	//���㾵�淴��
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_Viewpos - v_Fragpos);
	vec3 reflectDir = reflect(-lightDir, norm);//-lightDir ����Ϊreflect���ܵ���lightPos �� Fragpos������
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

	vec3 specular = specularStrength * spec * u_LightColor;
	
	//������
	vec3 result = (diffuse + ambient + specular) * u_ObjectColor;
	FragColor = vec4(result, 1.0f);
}