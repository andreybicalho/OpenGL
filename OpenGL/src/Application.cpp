#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;	

	// enforcing opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// screen updates (vsync) higher values means lower refresh hates
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	// opengl version
	std::cout << glGetString(GL_VERSION) << std::endl;


	{
		// points in space (our vertices)
		float positions[] = {
			100.f, 100.f, 0.0f, 0.0f,  // 0 
			200.f, 100.f, 1.0f, 0.0f,  // 1
			200.f, 200.f, 1.0f, 1.0f,  // 2
			100.f, 200.f, 0.0f, 1.0f   // 3
		};

		// indexes to draw a triangle from positions points
		unsigned int indices[] = {
			0, 1, 2, // one triangle (positions[0], positions[1], positions[2])
			2, 3, 0 // another triangle (positions[2], positions[3], positions[0])
		};



		/*
		Pipeline for drawing things:
		1 - bind our vertex buffer
		2 - setup our vertex layout (memory layout)
		3 - bind our index buffer
		4 - bind our shader
		5 - call our draw call
		*/

		VertexBuffer vb(positions, 4 * 4 * sizeof(float)); // 4 points in space represented by 4 values of float size (4 floats per vertex)
		VertexBufferLayout layout;
		layout.Push<float>(2); // 2 values of float size
		layout.Push<float>(2); // for our texture
		
		GLCall(glEnable(GL_BLEND)); // enabling transparency
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		va.AddBuffer(vb, layout);
		
		IndexBuffer ib(indices, 6); // 6 points in space (two triangles forming a square)
		
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f); 
		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(-100, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(200, 200, 0));
		
		glm::mat4 mvp = proj * view * model; // multiplication must be pvm and not mpv
		
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f); // our parameter in the shader program
		shader.SetUniformMat4f("u_MVP", mvp);

		Texture texture("res/textures/opengl_logo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0); // second parameter '0' has to match the slot we bound our texture (if we bind to slot 2: texture.Bind(2); we should pass 2 here)

		// clearing everything
		va.Unbind();
		vb.Unbind();
		ib.Unbind();		
		shader.Unbind();

		Renderer renderer; // our renderer

		float r = 0.0f;
		float increment = 0.05f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			renderer.Draw(va, ib, shader);



			// blink color
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;





			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}