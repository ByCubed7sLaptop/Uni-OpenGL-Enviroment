#pragma once

#include <string>

#include <glad.h>

struct Texture {
    GLuint id;
    std::string type;
    std::string path;
};