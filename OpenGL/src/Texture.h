#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int RendererID;
	std::string FilePath;
	unsigned char* LocalBuffer;
	int Width, Height, BytesPerPixel;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return Width; }
	inline int GetHeight() const { return Height; }
};