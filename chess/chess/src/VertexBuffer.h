#pragma once
#include <GL/glew.h>

class VertexBuffer {
public:
	VertexBuffer(const float* vertices, const float&& size) {
		glGenBuffers(1, &vbID);
		glBindBuffer(GL_ARRAY_BUFFER, vbID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	~VertexBuffer() {
		glDeleteBuffers(1, &vbID);
	}

	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;

	void Bind();
	void Unbind();

private:
	unsigned int vbID;
};