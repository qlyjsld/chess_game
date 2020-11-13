#pragma once
#include <GL/glew.h>
#include <vector>

class VertexArray {
public:

	VertexArray()
		: m_stride(0), attrib_counter(0)
	{
		glGenVertexArrays(1, &vaID);
		glBindVertexArray(vaID);
	}

	~VertexArray() {
		glDeleteVertexArrays(1, &vaID);
	}

	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;

	template<typename T>
	void attrib(unsigned int count) {
		static_assert(false);
	}

	template<>
	void attrib<float>(unsigned int count) {
		m_stride += count * sizeof(GLfloat);
		counts.push_back(count);
		attrib_counter++;
	}

	void EnableAttrib();
	void Bind();
	void Unbind();
private:
	unsigned int vaID;
	unsigned int m_stride;
	unsigned int attrib_counter;
	std::vector<unsigned int> counts;
};