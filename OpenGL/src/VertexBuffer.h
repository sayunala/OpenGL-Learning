#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct vec2
{
	float x, y;
};
struct  vec4
{
	float x, y, z, w;
};
struct Vertex
{
	vec2 Position;
	vec2 TexCoords;
	vec4 Color;
	float TexID;

};
class VertexBuffer
{
private:
	unsigned int m_RenderID;
public:
	VertexBuffer(const void* data, const unsigned int size);
	
	VertexBuffer(const void* data, const unsigned int size, unsigned int usage);
	VertexBuffer();

	~VertexBuffer();
	void Bind() const;
	void UnBind() const;

	void SubData(const unsigned int size, const Vertex* data) const;


};

