#include "Test.h"
#include <vender/imgui/imgui.h>
namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tess) {
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}

}