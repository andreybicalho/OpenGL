#include "TestClearColor.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {


	TestClearColor::TestClearColor()
		: ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}

	TestClearColor::~TestClearColor()
	{

	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", ClearColor);
	}

}