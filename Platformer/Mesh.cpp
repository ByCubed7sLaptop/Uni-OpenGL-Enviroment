#include "Mesh.h"

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

Mesh::Mesh(): shape(Shape::Cube()), VAO(0), VBO(0)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(shape.vertices), &shape.vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Mesh::~Mesh()
{
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
}

void Mesh::SetShape(Shape& newShape)
{
    this->shape = newShape;
} 

void Mesh::Draw(Shader shader, glm::vec3 pos, glm::quat quat)
{
    //glBindVertexArray(VAO);
    // Calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, pos);

    glm::mat4 rot = glm::mat4_cast(quat);
    model *= rot;

    shader.SetUniform("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}