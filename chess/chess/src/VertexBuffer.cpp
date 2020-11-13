#include "VertexBuffer.h"

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
