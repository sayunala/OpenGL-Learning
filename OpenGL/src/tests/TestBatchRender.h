#pragma once
#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include <array>
namespace test
{
	class TestBatchRender :
		public Test
	{
	public:
		TestBatchRender();
		~TestBatchRender();
		void OnUpdate(float deltatime)override;
		void OnImGuiRender() override;
		void OnRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture[2];

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
		float m_BotColorPosition[2] = {100.0f, 100.0f};
		float m_BotbwPosition[2] = {300.0f, 100.0f};

		std::array<Vertex, 4> CreateQuad(const float& x, const float& y, const float TexID);
	};
}