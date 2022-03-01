#include "Texture.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>
//#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>

Texture::Texture()
{
    this->type = type;
}

bool Texture::LoadFromFile(std::string filepath) {
     path = filepath;

     glGenTextures(1, &id);
     glBindTexture(GL_TEXTURE_2D, id);

     // Set wrapping parameters
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

     // Set filtering parameters
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

     // Load image, create texture and generate mipmaps
     int nrChannels;
     stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
     unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

     if (!data)
         std::cout << "[Texture::LoadFromFile] Failed to load texture" << std::endl;

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
     glGenerateMipmap(GL_TEXTURE_2D);

     stbi_image_free(data);

     return true;
 }