#include "Texture.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: RendererID(0), FilePath(path), LocalBuffer(nullptr), Width(0), Height(0), BytesPerPixel(0)
{
	stbi_set_flip_vertically_on_load(1); // NOTE(andrey): OpenGL 0,0 coordinates is at left bottom, generally images 0,0 are upper left corner so we need to flip it... xD
	LocalBuffer = stbi_load(path.c_str(), &Width, &Height, &BytesPerPixel, 4);

	GLCall(glGenTextures(1, &RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (LocalBuffer)
	{
		stbi_image_free(LocalBuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &RendererID));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	GLCall(glActiveTexture(GL_TEXTURE0+slot)); // OpenGL has 32 slots for PC... mobile is something like 8, it depends on the platform
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

