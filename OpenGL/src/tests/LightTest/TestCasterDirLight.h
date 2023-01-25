#pragma once

#include "tests/Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>

namespace test
{
	class TestCasterDirLight :
		public Test
	{
	public:
		TestCasterDirLight();
		~TestCasterDirLight();
		void OnUpdate(float deltatime)override;

		void OnImGuiRender() override;
		void OnRender() override;
		void processInput(GLFWwindow* window, float deltaTime)override;
		//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void setCamera(Camera* camera) override;

	private:
		std::unique_ptr<VertexArray> m_VAO, m_LightVAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader, m_LightShader;
		std::unique_ptr<Texture>m_Maps[3];

		glm::mat4 m_Proj, m_View, m_Model;
		glm::vec3 m_TranslationA, m_TranslationB;
		glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		Camera* m_camera;

		glm::vec3 cubePositions[10] = {
			  glm::vec3(0.0f,  0.0f,  0.0f),
			  glm::vec3(2.0f,  5.0f, -15.0f),
			  glm::vec3(-1.5f, -2.2f, -2.5f),
			  glm::vec3(-3.8f, -2.0f, -12.3f),
			  glm::vec3(2.4f, -0.4f, -3.5f),
			  glm::vec3(-1.7f,  3.0f, -7.5f),
			  glm::vec3(1.3f, -2.0f, -2.5f),
			  glm::vec3(1.5f,  2.0f, -2.5f),
			  glm::vec3(1.5f,  0.2f, -1.5f),
			  glm::vec3(-1.3f,  1.0f, -1.5f)
		};
	};
}