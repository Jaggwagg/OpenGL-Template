#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
private:
    void checkCompileErrors(GLuint shader, std::string type);

public:
    GLuint pShader;

    Shader(const char* vShaderCodeFilePath, const char* fShaderCodeFilePath);

    void use();

    void setBool(const std::string& name, GLboolean value) const;

    void setInt(const std::string& name, GLint value) const;

    void setFloat(const std::string& name, GLfloat value) const;

    void setMat4(const std::string& name, glm::mat4 value) const;
};

#endif