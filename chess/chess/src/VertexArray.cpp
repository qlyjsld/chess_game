#include "VertexArray.h"

void VertexArray::Bind() {
	glBindVertexArray(vaID);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

void VertexArray::EnableAttrib() {
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attrib_counter; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, counts[i], GL_FLOAT, GL_FALSE, m_stride, (const void*)offset);
		offset += counts[i] * sizeof(float);
	}
}