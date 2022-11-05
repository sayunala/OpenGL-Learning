#pragma once
class VertexBuffer
{
private:
	unsigned int m_RenderID;
public:
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;


};

