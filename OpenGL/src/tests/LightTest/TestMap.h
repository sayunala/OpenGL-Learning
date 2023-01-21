#pragma once

#include "tests/Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>

namespace test
{
	class TestMap :
		public Test
	{
	public:
		TestMap();
		~TestMap();
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

	};
}