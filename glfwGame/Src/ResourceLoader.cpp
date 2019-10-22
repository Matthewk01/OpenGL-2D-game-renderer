//
// Created by matej on 14/09/2019.
//


#include "ResourceLoader.hpp"
#include <iostream>
#include <stb_image.h>
#include "glad/glad.h"

std::map<std::string, unsigned int> ResourceLoader::textures{};

void ResourceLoader::createTexture(const std::string &textureName, const std::string &texturePath, bool transparent) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height,
                                    &nrChannels, 0);
    if (data) {
        if (transparent) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    textures[textureName] = texture;
    stbi_image_free(data);
}

unsigned int ResourceLoader::getTextureID(const std::string &textureName) {
    return textures[textureName];
}
