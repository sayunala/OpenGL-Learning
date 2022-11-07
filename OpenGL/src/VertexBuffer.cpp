#include "VertexBuffer.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, const unsigned int size)
{
	
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));//绑定当前缓冲区
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int size, unsigned int usage)
{
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));//绑定当前缓冲区
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
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));//绑定当前缓冲区
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));//绑定当前缓冲区
}

void VertexBuffer::SubData(const unsigned int size,const Vertex* data) const
{
	int n = sizeof(data);
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
