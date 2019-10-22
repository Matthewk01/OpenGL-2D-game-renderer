//
// Created by matej on 14/09/2019.
//

#ifndef GLFWTEST_RESOURCELOADER_HPP
#define GLFWTEST_RESOURCELOADER_HPP

#include <string>
#include <map>


class ResourceLoader {
private:
    static std::map<std::string, unsigned int> textures;
public:
    static void createTexture(const std::string &textureName, const std::string &texturePath, bool transparent);

    static unsigned int getTextureID(const std::string &textureName);
};


#endif //GLFWTEST_RESOURCELOADER_HPP
