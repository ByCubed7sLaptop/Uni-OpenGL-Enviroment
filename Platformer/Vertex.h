#pragma once

#include <glm/glm.hpp>

struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;

    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 coord) : Position(pos), Normal(norm), TexCoords(coord) {}
};

