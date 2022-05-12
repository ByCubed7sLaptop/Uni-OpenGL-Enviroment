#include "Mesh.h"

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

Mesh::Mesh(): shape(Shape::Cube()), VAO(0), VBO(0)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.size() * sizeof(Vertex), &shape.vertices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
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
    glBindVertexArray(VAO);
    
    // Calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, pos);
    
    quat = glm::normalize(quat);
    glm::mat4 rot = glm::mat4_cast(quat);
    
    // Apply the matrix
    model *= rot;

    shader.SetUniform("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader, glm::vec3 pos, glm::vec3 euler)
{
    //glm::quat aroundX = glm::quat(1.0f, 0.0f, 0.0f, euler.x);
    //glm::quat aroundY = glm::quat(0.0f, 1.0f, 0.0f, euler.y);
    //glm::quat aroundZ = glm::quat(0.0f, 0.0f, 1.0f, euler.z);
    //glm::quat finalOrientation = aroundX * aroundY * aroundZ;

    Draw(shader, pos, glm::quat(euler));
}
