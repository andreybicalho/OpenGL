#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> VAO;
		std::unique_ptr<IndexBuffer> IBO;
		std::unique_ptr<VertexBuffer> VBO;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Texture> texture;

		glm::vec3 TranslationA, TranslationB;
		glm::mat4 Proj, View;
	};
}
