#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

#include <vector>
#include <sstream>

#include <glad.h>
//#include "GL/freeglut.h"
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// The “Named Constructor Idiom”?
// https://isocpp.org/wiki/faq/ctors#named-ctor-idiom


class Shape {
public:

    // Copy constructor
    Shape(const Shape& oldShape);

    std::vector<Vertex> vertices;

    // Constructor
    Shape(std::vector<Vertex> vertices);

    static Shape Cube();
};