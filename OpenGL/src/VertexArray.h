#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RenderID;
public:
	void AddBufferLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;

};

