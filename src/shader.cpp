#include "shader.h"

#include <glad/glad.h>

Shader::Shader(const char* vShaderCodeFilePath, const char* fShaderCodeFilePath) {
    std::string vShaderCodeString;
    std::string fShaderCodeString;
    std::ifstream vShaderCodeFile;
    std::ifstream fShaderCodeFile;

    vShaderCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderCodeFile.open(vShaderCodeFilePath);
        fShaderCodeFile.open(fShaderCodeFilePath);

        std::stringstream vShaderCodeStream;
        std::stringstream fShaderCodeStream;

        vShaderCodeStream << vShaderCodeFile.rdbuf();
        fShaderCodeStream << fShaderCodeFile.rdbuf();

        vShaderCodeFile.close();
        fShaderCodeFile.close();

        vShaderCodeString = vShaderCodeStream.str();
        fShaderCodeString = fShaderCodeStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "OPENGL_SHADER: FILE NOT SUCCESSFULLY READ\n";
    }

    const char* vShaderCode = vShaderCodeString.c_str();
    const char* fShaderCode = fShaderCodeString.c_str();

    unsigned int vShader, fShader;

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderCode, NULL);
    glCompileShader(vShader);
    checkCompileErrors(vShader, "VERTEX");

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderCode, NULL);
    glCompileShader(fShader);
    checkCompileErrors(fShader, "FRAGMENT");

    pShader = glCreateProgram();
    glAttachShader(pShader, vShader);
    glAttachShader(pShader, fShader);
    glLinkProgram(pShader);
    checkCompileErrors(pShader, "PROGRAM");

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use() {
    glUseProgram(pShader);
}

void Shader::Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(pShader, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(pShader, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(pShader, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[512];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "OPENGL_SHADER_" << type << ": FAILED TO COMPILE SHADER: \n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(pShader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "OPENGL_SHADER_" << type << ": FAILED TO LINK SHADER(S): \n" << infoLog << std::endl;
        }
    }
}