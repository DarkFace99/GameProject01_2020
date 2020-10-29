#pragma once

#include <GLM.hpp>
#include <vector>

class Vertex {
public:
	Vertex();
	Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 textureCoordinate);

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();

	void SetColor(glm::vec3 color);
	glm::vec3 GetColor();

	void SetTexCoords(glm::vec2 TexCoords);
	glm::vec2 GetTexCoords();

	std::vector<float> GetDataArray();

	glm::vec3 position;		// x, y, z
	glm::vec3 color;		// r, g, b
	glm::vec2 texCoords;	// u, v
};