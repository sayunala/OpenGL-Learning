#version 330 core
out vec4 FragColor;
//uniform  vec3 u_ObjectColor;
//uniform vec3 u_LightColor;

uniform vec3 u_Lightpos;//�ƹ�λ��
uniform vec3 u_Viewpos;// �۾�λ��
in vec3 v_Normal;//������
in vec3 v_Fragpos;//���ص�����λ�ü�����ߵ�
in vec2 v_TexCoords;// ��ͼ����


struct Material{
	sampler2D diffuse;//����������±�����ɫ 
	sampler2D specular;// �����Ͼ���߹����ɫ
	sampler2D emission;
	float shinines;
};

struct Light{
	vec3 direction;
	vec3 position;
	float cutoff;
	float outercutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

uniform Material u_Material;
uniform Light u_Light;
uniform float u_Matrixlight;
uniform float u_Matrixmove;

void main(){
	vec3 lightDir = normalize(u_Light.position - v_Fragpos);

	float theta = dot(lightDir, normalize(-u_Light.direction));
	float epsilon = u_Light.cutoff - u_Light.outercutoff;
	float intensity = clamp((theta - u_Light.outercutoff) / epsilon, 0.0, 1.0);

	float ambienStrength = 0.1;
	vec3 ambient =  u_Light.ambient;//������ǿ

	//�����������ǿ
	vec3 norm = normalize(v_Normal);

	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_Light.diffuse;

	//���㾵�淴��
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_Viewpos - v_Fragpos);
	vec3 reflectDir = reflect(-lightDir, norm);//-lightDir ����Ϊreflect���ܵ���lightPos �� Fragpos������
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shinines);
	vec3 specular =  spec * u_Light.specular;

	vec3 emission = u_Matrixlight*texture(u_Material.emission, v_TexCoords + vec2(0.0, u_Matrixmove)).rgb;
	
	

	// Ƭ����ɫ
	vec3 ambientLight = ambient * vec3(texture(u_Material.diffuse, v_TexCoords));
	vec3 diffuseLight = diffuse * vec3(texture(u_Material.diffuse, v_TexCoords));
	vec3 specularLight = specular * vec3(texture(u_Material.specular, v_TexCoords));

	diffuseLight *= intensity;
	specularLight *= intensity;
	//������
	vec3 result = diffuseLight + ambientLight + specularLight;
	FragColor = vec4(result, 1.0f);
	

}