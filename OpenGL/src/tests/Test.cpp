#include "Test.h"
#include "imgui/imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer)
		: CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : Tests)
		{ 
			if(ImGui::Button(test.first.c_str()))
			{
				CurrentTest = test.second();
			}
		}
	}

}