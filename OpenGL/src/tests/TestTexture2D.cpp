#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {


	TestTexture2D::TestTexture2D()
		: TranslationA(200, 200, 0), TranslationB(400, 200, 0),
		Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f)), 
		View(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)))
	{
		// points in space (our vertices and also our texture coordinates)
		float positions[] = {
			-50.f, -50.f, 0.0f, 0.0f,  // 0 
			50.f, -50.f, 1.0f, 0.0f,  // 1
			50.f,  50.f, 1.0f, 1.0f,  // 2
			-50.f,  50.f, 0.0f, 1.0f   // 3
		};

		// indexes to draw a triangle from positions points
		unsigned int indices[] = {
			0, 1, 2, // one triangle (positions[0], positions[1], positions[2])
			2, 3, 0 // another triangle (positions[2], positions[3], positions[0])
		};

		
		GLCall(glEnable(GL_BLEND)); // enabling transparency
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VAO = std::make_unique<VertexArray>();
		VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float)); // 4 points in space represented by 4 values of float size (4 floats per vertex)
		VertexBufferLayout layout;
		layout.Push<float>(2); // 2 values of float size
		layout.Push<float>(2); // for our texture

		VAO->AddBuffer(*VBO, layout);
		IBO = std::make_unique<IndexBuffer>(indices, 6); // 6 points in space (two triangles forming a square)

		shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		shader->Bind();
		shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		texture = std::make_unique<Texture>("res/textures/opengl_logo.png");
		shader->SetUniform1i("u_Texture", 0); // second parameter '0' has to match the slot we bound our texture (if we bind to slot 2: texture.Bind(2); we should pass 2 here)
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		texture->Bind();

		// first logo
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), TranslationA);
			glm::mat4 mvp = Proj * View * model;
			shader->Bind(); // NOTE(andrey): we need bind it once since Draw() will bind things also, so it would be waist of performance
			shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*VAO, *IBO, *shader);
		}

		// second logo
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), TranslationB);
			glm::mat4 mvp = Proj * View * model;
			shader->Bind();
			shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*VAO, *IBO, *shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("TranslationB", &TranslationB.x, 0.0f, 960.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}