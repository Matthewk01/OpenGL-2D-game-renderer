//
// Created by matej on 07/09/2019.
//

#ifndef GLFWTEST_SHADER_HPP
#define GLFWTEST_SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setTransform(const std::string &matrixName, glm::mat4 transformMatrix);

private:
    unsigned int programID;
};


#endif //GLFWTEST_SHADER_HPP
