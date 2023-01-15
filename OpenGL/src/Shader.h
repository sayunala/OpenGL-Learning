#pragma once
#include <unordered_map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<tuple>
#include "glm/glm.hpp"

class Shader
{
private:
	unsigned int m_RenderID;
	std::string m_FliePath;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	Shader(const std::string& vertexshader, const std::string& fragmentshader);
	~Shader();
	void Bind() const;
	void UnBind() const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) ;
	void SetUniform3f(const std::string& name, float v0, float v1, float v2) ;
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform1i(const std::string& name, int i);
	void SetUniform1iv(const std::string& name, int count, int* value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& proj);
	
private:
	std::tuple<std::string, std::string> ParseShader(const std::string& filepath);
	std::string ParseSingleShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);

	int GetUniformLocation(const std::string& name) const;
};

