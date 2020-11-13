#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


void Shader::Bind() {
	glUseProgram(programID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	else {
		int location = glGetUniformLocation(programID, name.c_str());
		if (location == -1)
			std::cout << "Warning: Uniform" << name << " doesn't exist!" << std::endl;
		m_UniformLocationCache[name] = location;
		return location;
	}
}

void Shader::updateOffset(const std::string& name, const glm::vec2& offset) {
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(offset));
}