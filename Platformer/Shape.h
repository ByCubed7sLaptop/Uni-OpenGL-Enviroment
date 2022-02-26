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
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    // Constructor
    Shape(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

    // Render the mesh
    void Draw(Shader shader);

private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;

    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void SetupMesh();
};