#include "TestMaterial.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
namespace test
{
	TestMaterial::TestMaterial()
		:m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f))),
		m_Model(glm::mat4(1.0f)),
		m_TranslationA(glm::vec3(200, 200, 0)), m_TranslationB(glm::vec3(400, 200, 0))

	{

		//m_window = window;
		//glfwSetCursorPosCallback(m_window, mouse_callback);
		m_View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		const int vertexcount = 36;

		float positions[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, vertexcount * 6 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);

		m_VAO->AddBufferLayout(*m_VertexBuffer, layout);
		m_LightVAO = std::make_unique<VertexArray>();
		//m_LightVAO->Bind();
		m_LightVAO->AddBufferLayout(*m_VertexBuffer, layout);
		m_Shader = std::make_unique<Shader>("res/Shaders/LearningOpenglShader/Light/CubeVertexShader.vert", "res/Shaders/LearningOpenglShader/Light/MaterialFragShader.frag");
		m_LightShader = std::make_unique<Shader>("res/Shaders/LearningOpenglShader/Light/LightVertexShader.vert", "res/Shaders/LearningOpenglShader/Light/LightFragShader.frag");
		//m_Shader->Bind();
		//m_Texture = std::make_unique<Texture>("res/Textures/LearnOpenglTextures/awesomeface.png");

	}

	TestMaterial::~TestMaterial()
	{
	}

	void TestMaterial::OnUpdate(float deltaTime)
	{

	}

	void TestMaterial::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));


		Renderer renderer;

		{
			float radius = 10.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;

			glm::mat4 view = m_camera->GetViewMatrix();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Cube渲染
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 0.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 mvp = m_Proj * view * model;
			m_View = view;
			m_Model = model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			//材质着色器

			m_Shader->SetUniform3f("u_Material.ambient", 1.0f, 0.5f, 0.31f);
			m_Shader->SetUniform3f("u_Material.diffuse", 1.0f, 0.5f, 0.31f);
			m_Shader->SetUniform3f("u_Material.specular", 0.5f, 0.5f, 0.5f);
			m_Shader->SetUniform1f("u_Material.shinines", 32.0f);
			//灯光属性设置
			glm::vec3 lightColor;
			lightColor.x = sin(glfwGetTime() * 2.0f);
			lightColor.y = sin(glfwGetTime() * 0.7f);
			lightColor.z = sin(glfwGetTime() * 1.3f);

			glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

			m_Shader->SetUniformVec3f("u_Light.ambient", ambientColor);
			m_Shader->SetUniformVec3f("u_Light.diffuse", diffuseColor); // 将光照调暗了一些以搭配场景
			m_Shader->SetUniform3f("u_Light.specular", 1.0f, 1.0f, 1.0f);
			glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
			m_Shader->SetUniform3f("u_Light.position", lightPos.x, lightPos.y, lightPos.z);
			


			m_Shader->SetUniformMat4f("u_Model", model);
			m_Shader->SetUniformMat4f("u_View", view);
			m_Shader->SetUniformMat4f("u_Projection", m_Proj);
			
			m_Shader->SetUniformVec3f("u_Viewpos", m_camera->Position);
			renderer.DrawArrays(*m_VAO, *m_Shader, 36);

			//灯光渲染
			m_LightShader->Bind();

			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			mvp = m_Proj * view * model;
			m_LightShader->SetUniformMat4f("u_MVP", mvp);
			renderer.DrawArrays(*m_LightVAO, *m_LightShader, 36);

		}



	}

	void TestMaterial::processInput(GLFWwindow* window, float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		float cameraSpeed = static_cast<float>(2.5 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			//m_cameraPos += cameraSpeed * m_cameraFront;
			m_camera->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_camera->ProcessKeyboard(BACKWARD, deltaTime);
		//m_cameraPos -= cameraSpeed * m_cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_camera->ProcessKeyboard(LEFT, deltaTime);
		//m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_camera->ProcessKeyboard(RIGHT, deltaTime);
		//m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
	}

	void TestMaterial::setCamera(Camera* camera)
	{
		m_camera = camera;

	}



	void TestMaterial::OnImGuiRender()
	{
		ImGui::SliderFloat3("m_TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("m_TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
