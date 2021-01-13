#include <GL/glew.h>

#include "Vertex.h"

class Mesh {
public:
	GLuint vao; // vertex array object
	GLuint vertexBuffer;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	std::vector<Vertex> vertex;
};