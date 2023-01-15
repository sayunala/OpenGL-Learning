#pragma once
#include <vector>
#include <functional>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
namespace test {
	class Test
	{
	public:
		Test() {};
		//Test(GLFWwindow* window) { m_window = window; };
		virtual ~Test() {};
		virtual void OnUpdate(float deltatime) {
		
		};
	
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
		virtual void processInput(GLFWwindow* window, float deltaTime) {};
		virtual void mouse_callback(GLFWwindow* window, double xpos, double ypos) {};
		
		
		virtual void setCamera( Camera* camera){};
	};

	class TestMenu:public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		virtual void OnImGuiRender() override;
		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tess.push_back(std::make_pair(name.c_str(), []() {return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tess;
	};

	

}