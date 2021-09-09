#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
private:
    void checkCompileErrors(unsigned int shader, std::string type);

public:
    unsigned int pShader;

    Shader(const char* vShaderCodeFilePath, const char* fShaderCodeFilePath);

    void use();

    void setBool(const std::string& name, bool value) const;

    void setInt(const std::string& name, int value) const;

    void setFloat(const std::string& name, float value) const;

    //void setMat4(const std::string& name, int value) const;
};

#endif