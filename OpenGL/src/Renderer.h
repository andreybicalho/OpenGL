#pragma once

#include "GL/glew.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);



/*
 Requirements: (what things do we need in order to draw something on screen?)
 1 - index buffer
 2 - vertex array
 3 - a valid shader
*/

class Renderer
{
private:

public:
	//Renderer();
	//~Renderer();
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
