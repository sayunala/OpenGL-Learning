#include "TestBatchRender.h"


#include "TestBatchRender.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test
{
	
	
	TestBatchRender::TestBatchRender()
		:m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0))),
		m_TranslationA(glm::vec3(200, 200, 0)), m_TranslationB(glm::vec3(400, 200, 0))
	{
		
		float positions[] = {
			100.0f, 100.0f, 0.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,// 0
			200.0f, 100.0f, 1.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,// 1
			200.0f, 200.0f, 1.0f, 1.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,  // 2
			100.0f, 200.0f, 0.0f, 1.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, // 3

			300.0f, 100.0f, 0.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f,// 4
			400.0f, 100.0f, 1.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f,// 5
			400.0f, 200.0f, 1.0f, 1.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f,  // 6
			300.0f, 200.0f, 0.0f, 1.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f // 7
		};

	/*	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
		};*/
		unsigned int indices[MaxIndexCount];
		unsigned int offset = 0;
		for (int i = 0; i < MaxIndexCount; i += 6) {

			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex)*MaxVertexCount,GL_DYNAMIC_DRAW);
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		layout.Push<float>(4);
		layout.Push<float>(1);

		m_VAO->AddBufferLayout(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, MaxIndexCount);

		m_Shader = std::make_unique<Shader>("res/Shaders/Batch.shader");
		m_Shader->Bind();


		m_Texture[0] = std::make_unique<Texture>("res/Textures/bot_color.png");
		m_Texture[1] = std::make_unique<Texture>("res/Textures/bot_bw.png");
		for (unsigned int i = 0; i < 2; i++)
		{
			m_Texture[i]->Bind(i);
		}
		int sample2D[2] = { 0,1 };
		m_Shader->SetUniform1iv("u_Textures", 2, sample2D);
		
		
	}

	TestBatchRender::~TestBatchRender()
	{
	}

	void TestBatchRender::OnUpdate(float deltaTime)
	{
		std::array<Vertex, MaxVertexCount> manyVertices;
		Vertex* buffer = manyVertices.data();
		unsigned int indexcount = 0;
		for (int y = 0; y < 500; y += 100)
		{
			for (int x = 0; x < 500; x += 100)
			{
				buffer = CreateQuad(buffer, x, y, ((x + y) % 200) / 100);
				indexcount += 6;
			}
		}

		auto Quad0=CreateQuad(m_BotColorPosition[0], m_BotColorPosition[1], 0.0f);
		auto Quad1=CreateQuad(m_BotbwPosition[0], m_BotbwPosition[1], 1.0f);
		Vertex vertices[8];
		memcpy(vertices, Quad0.data(), sizeof(Quad0));
		memcpy(vertices + 4, Quad1.data(), sizeof(Quad0));

		m_VertexBuffer->Bind();
		m_VertexBuffer->SubData(sizeof(manyVertices), manyVertices.data());
	
		 
	/*	VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		layout.Push<float>(4);
		layout.Push<float>(1);

		m_VAO->AddBufferLayout(*m_VertexBuffer, layout);
	
		m_Shader->Bind();


		for (unsigned int i = 0; i < 2; i++)
		{
			m_Texture[i]->Bind(i);
		}
		int sample2D[2] = { 0,1 };
		m_Shader->SetUniform1iv("u_Textures", 2, sample2D);*/
		
	}

	void TestBatchRender::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;


		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		/*	{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
				glm::mat4 mvp = m_Proj * m_View * model;

				m_Shader->Bind();
				m_Shader->SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
			}*/
	}

	std::array<Vertex, 4> TestBatchRender::CreateQuad(const float& x, const float& y, const float TexID)
	{
		Vertex v0;
		v0.Position = { x ,y };
		v0.TexCoords = { 0.0f, 0.0f };
		v0.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v0.TexID = TexID;

		Vertex v1;
		v1.Position = { x + 100,y };
		v1.TexCoords = { 1.0f, 0.0f };
		v1.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v1.TexID = TexID;

		Vertex v2;
		v2.Position = { x + 100 ,y +100 };
		v2.TexCoords = { 1.0f, 1.0f };
		v2.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v2.TexID = TexID;

		Vertex v3;
		v3.Position = { x ,y + 100 };
		v3.TexCoords = { 0.0f, 1.0f };
		v3.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v3.TexID = TexID;
		return {v0,v1,v2,v3};
	}

	Vertex* TestBatchRender::CreateQuad(Vertex* target, const float& x, const float& y, const float TexID)
	{
		float size = 100.0f;
		
		target->Position = { x ,y };
		target->TexCoords = { 0.0f, 0.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexID = TexID;
		target++;
		
		target->Position = { x + size,y };
		target->TexCoords = { 1.0f, 0.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexID = TexID;
		target++;
		
		target->Position = { x + size ,y + 100 };
		target->TexCoords = { 1.0f, 1.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexID = TexID;
		target++;
	
		target->Position = { x ,y + size };
		target->TexCoords = { 0.0f, 1.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexID = TexID;
		target++;
		return target;
	}

	void TestBatchRender::OnImGuiRender()
	{
		ImGui::SliderFloat3("m_TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("m_TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::DragFloat2("bot_color Position", m_BotColorPosition, 25.0f);
		ImGui::DragFloat2("bot_bw Position", m_BotbwPosition, 25.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
