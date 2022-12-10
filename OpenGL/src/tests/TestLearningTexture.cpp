#include "TestLearningTexture.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
namespace test
{
	TestLearningTexture::TestLearningTexture()
		:m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0))),
		m_TranslationA(glm::vec3(200, 200, 0)), m_TranslationB(glm::vec3(400, 200, 0))
	{
		float positions[] = {
			//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 8 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBufferLayout(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/Shaders/LearningOpenglShader/vertexshader.glsl","res/Shaders/LearningOpenglShader/fragmentshader.glsl");
		m_Shader->Bind();

	

		m_Texture = std::make_unique<Texture>("res/Textures/LearnOpenglTextures/awesomeface.png");
		m_Textures[0] = std::make_unique<Texture>("res/Textures/LearnOpenglTextures/awesomeface.png"); 
		m_Textures[1] = std::make_unique<Texture>("res/Textures/bot_color.png");
		for (unsigned int i = 0; i < 2; i++)
		{
			m_Textures[i]->Bind(i);

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		}
		int sampler2D[2] = { 0,1 };
		m_Shader->SetUniform1iv("u_Textures", 2, sampler2D);
	}

	TestLearningTexture::~TestLearningTexture()
	{
	}

	void TestLearningTexture::OnUpdate(float deltaTime)
	{

	}

	void TestLearningTexture::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, +0.5f, 0.0f));
		trans = glm::rotate(trans,(float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		float scaleAmount = static_cast<float>(sin(glfwGetTime()));
		trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, 1.0));
		
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", trans);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		

	
	}

	void TestLearningTexture::OnImGuiRender()
	{
		ImGui::SliderFloat3("m_TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("m_TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
