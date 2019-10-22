//
// Created by matej on 07/09/2019.
//

#include "Shader.hpp"
#include <glad/glad.h>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    std::ifstream vertexFile(vertexShaderPath);
    std::ifstream fragmentFile(fragmentShaderPath);
    if (vertexFile.fail() || fragmentFile.fail()) {
        throw std::exception();
    }
    std::string vertexSource;
    std::string fragmentSource;
    std::string tmpStr;
    while (std::getline(vertexFile, tmpStr)) {
        vertexSource += tmpStr + '\n';
    }
    while (std::getline(fragmentFile, tmpStr)) {
        fragmentSource += tmpStr + '\n';
    }
    const char *vertexSource2 = vertexSource.c_str();
    const char *fragmentSource2 = fragmentSource.c_str();
    int success;
    char log[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource2, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource2, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
    }
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINK\n" << log << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this->programID = shaderProgram;
}

void Shader::use() {
    glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);
}

void Shader::setTransform(const std::string &matrixName, glm::mat4 transformMatrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->programID, matrixName.c_str()), 1, GL_FALSE,
                       glm::value_ptr(transformMatrix));
}
