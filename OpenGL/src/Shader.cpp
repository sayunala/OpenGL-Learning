#include "Shader.h"
#include "Renderer.h"
Shader::Shader(const std::string& filepath)
	:m_FliePath(filepath)
{
	auto [vertexSource, fragmentSource] = ParseShader(filepath);
	m_RenderID = CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RenderID));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}


std::tuple<std::string, std::string> Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType {
		None = -1,
		Vertex = 0,
		Fragment = 1
	};
	ShaderType type = ShaderType::None;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::Vertex;
			else
				type = ShaderType::Fragment;
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}
	return std::tuple<std::string, std::string>(ss[0].str(), ss[1].str());

}
/*
* 编译着色器
*/
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);//绑定着色器代码，生成着色器
	glCompileShader(id);//编译id表示的着色器

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);//获取当前编译状态
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);//获取需要打印的编译信息长度
		char* message = (char*)_malloca(sizeof(char) * length);
		glGetShaderInfoLog(id, length, &length, message);//获取编译失败日志

		std::cout << "Failed to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< "shader" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);//编译失败删除id指向的着色器
		return 0;
	}
	return id;

}
unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
	unsigned int program = glCreateProgram();//创建着色器程序
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vs);//将生成着色器附加到程序中
	glAttachShader(program, fs);
	glLinkProgram(program);//链接程序
	glValidateProgram(program);//验证程序的有效性

	glDeleteShader(vs);//删除已经没用的着色器
	glDeleteShader(fs);
	return program;
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_RenderID, name.c_str()));
	if (location == -1)
		std::cout << "warning:uniform" << name << "does not exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;

}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
	GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform1i(const std::string& name, int i)
{
	GLCall(glUniform1i(GetUniformLocation(name), i));
}
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& proj)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1 , GL_FALSE, &proj[0][0]));
}
