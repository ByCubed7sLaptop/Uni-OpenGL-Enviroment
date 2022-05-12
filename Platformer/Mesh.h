#pragma once


#include <vector>
#include "Shape.h"

class Mesh
{
public:
	Shape shape;
	std::vector<Texture> textures;

	// Render data
	//GLuint 
	unsigned int VAO, VBO;

	Mesh();
	~Mesh();
	void SetShape(Shape& newShape);

	void Draw(Shader shader, glm::vec3 pos, glm::quat quat);
	void Draw(Shader shader, glm::vec3 pos, glm::vec3 euler);
};

