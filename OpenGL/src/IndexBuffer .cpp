#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const void* data, const unsigned int count)
	:m_Count(count)
{
	
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));//绑定当前缓冲区
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count*sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderID));
}


void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));//绑定当前缓冲区
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));//绑定当前缓冲区
}
