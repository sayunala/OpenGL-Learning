#pragma once
#include <vector>
#include <functional>
namespace test {
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {};
		virtual void OnUpdate(float deltatime) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};

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