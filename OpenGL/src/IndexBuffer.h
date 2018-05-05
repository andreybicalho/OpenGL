#pragma once

class IndexBuffer
{
private:
	unsigned int RendererID;
	unsigned int Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const;

	inline unsigned int GetCount() { return Count; }
};