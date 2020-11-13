#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "glm/vec2.hpp"

class Shader {
public:
	Shader(const std::string& path) {
        programID = glCreateProgram();
        std::ifstream file(path, std::ifstream::in);
        std::string line;
        std::stringstream ss[3];
        unsigned int i = 0;
        while (getline(file, line)) {
            if (line.find("#shader vertex") != std::string::npos)
                i = 0;
            else if (line.find("#shader geometry") != std::string::npos)
                i = 1;
            else if (line.find("#shader fragment") != std::string::npos)
                i = 2;
            else
                ss[i] << line << "\n";
        }

        std::string vertex_shader = ss[0].str();
        std::string geometry_shader = ss[1].str();
        std::string fragment_shader = ss[2].str();

        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        const char* src = vertex_shader.c_str();
        glShaderSource(vs, 1, &src, nullptr);
        glCompileShader(vs);

        unsigned int gs = glCreateShader(GL_GEOMETRY_SHADER);
        src = geometry_shader.c_str();
        glShaderSource(gs, 1, &src, nullptr);
        glCompileShader(gs);

        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        src = fragment_shader.c_str();
        glShaderSource(fs, 1, &src, nullptr);
        glCompileShader(fs);

        glAttachObjectARB(programID, vs);
        glAttachObjectARB(programID, gs);
        glAttachObjectARB(programID, fs);
        glLinkProgram(programID);
        glValidateProgram(programID);

        glDeleteShader(vs);
        glDeleteShader(gs);
        glDeleteShader(fs);
	}

    ~Shader() {
        glDeleteProgram(programID);
    }

    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    void Bind();
    void Unbind();
    void updateOffset(const std::string& name, const glm::vec2& offset);

private:
	unsigned int programID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    int GetUniformLocation(const std::string& name);
};