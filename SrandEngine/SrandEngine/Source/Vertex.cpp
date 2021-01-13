#include "Vertex.h"

Vertex::Vertex()
{
	Vertex::position = glm::vec3(0, 0, 0);
	Vertex::color = glm::vec3(0, 0, 0);
	Vertex::texCoords = glm::vec2(0, 0);
}

Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 textureCoordinate)
{
	Vertex::position = position;
	Vertex::color = color;
	Vertex::texCoords = textureCoordinate;
}

void Vertex::SetPosition(glm::vec3 position) { Vertex::position = position; }
glm::vec3 Vertex::GetPosition() { return position; }

void Vertex::SetColor(glm::vec3 color) { Vertex::color = color; }
glm::vec3 Vertex::GetColor() { return color; }

void Vertex::SetTexCoords(glm::vec2 texCoords) { Vertex::texCoords = texCoords; }
glm::vec2 Vertex::GetTexCoords() { return texCoords; }

std::vector<float> Vertex::GetDataArray()
{
	std::vector<float> data;

	data.push_back(position.x);
	data.push_back(position.y);
	data.push_back(position.z);
	data.push_back(color.r);
	data.push_back(color.g);
	data.push_back(color.b);
	data.push_back(texCoords.x);
	data.push_back(texCoords.y);

	return data;
}