#pragma once

#include <vector>
#include <GL/glew.h>

#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}

		ASSERT(false); // just ensure it will never hit this place... if it does... well, we should have include another case
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> Elements;
	unsigned int Stride;
public:
	VertexBufferLayout() : Stride(0) {};

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT); //sizeof(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT); //sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE); //sizeof(GLbyte);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return Elements; }
	inline unsigned int GetStride() const { return Stride; }
};