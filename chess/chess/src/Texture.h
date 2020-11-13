#pragma once
#include <GL/glew.h>
#include <string>
#include "stb_image.h"

class Texture {
public:
	Texture(const std::string& path) {
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		if (m_LocalBuffer) {
			stbi_image_free(m_LocalBuffer);
		}
	}

	~Texture() {
		glDeleteTextures(1, &textureID);
	}

	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;

	void Bind();
	void Unbind();
private:
	unsigned int textureID;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_BPP;
};
