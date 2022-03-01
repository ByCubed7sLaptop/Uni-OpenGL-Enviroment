#include "Shape.h"

Shape::Shape(const Shape& oldShape)
{
    vertices = oldShape.vertices;
}

Shape::Shape(std::vector<Vertex> vertices)
{
    this->vertices = vertices;

}

Shape Shape::Cube()
{
    const std::vector<Vertex> vertices = std::vector<Vertex>(
        {
            Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Vertex({ 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ 0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ 0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),

            Vertex({ -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Vertex({ 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ 0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ 0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ -0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),

            Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),

            Vertex({ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ 0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ 0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Vertex({ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),

            Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ 0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ 0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),

            Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
            Vertex({ 0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
            Vertex({ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
            Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f })
        }
    );
    return Shape(vertices);
}