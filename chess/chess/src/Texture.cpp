#include "Texture.h"

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}