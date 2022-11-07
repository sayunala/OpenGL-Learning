#include "VertexBuffer.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, const unsigned int size)
{
	
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));//�󶨵�ǰ������
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int size, unsigned int usage)
{
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));//�󶨵�ǰ������
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}
VertexBuffer::VertexBuffer() {

}



VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1,&m_RenderID));
}


void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));//�󶨵�ǰ������
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));//�󶨵�ǰ������
}

void VertexBuffer::SubData(const unsigned int size,const Vertex* data) const
{
	int n = sizeof(data);
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
