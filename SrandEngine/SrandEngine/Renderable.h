#pragma once

#include <vector>

/* Typdef for Texture */
typedef GLuint Texture;

/* Vertex class declaration */
class Vertex {
	float x, y, z; // position
	float r, g, b; // color
	float u, v;    // corner
};

/* Mesh class declaration */
class Mesh {
	GLuint vao; // vertex array object
	GLuint vertexBuffer;
	glm::mat4 modelMatrix;
	std::vector<Vertex> vertex;
};

/* Renderable class declaration */
class Renderable {
private:
	int width;
	int height;
	int renderMode; // 0 = color, 1 = texture
	float transpareny; // Alpha value

public:
	Texture LoadTexture();
	void UnloadTexture(Texture texture);

	Mesh LoadMesh(std::vector<Vertex>);
	void DrawMesh(Mesh mesh);
	void UnloadMesh(Mesh mesh);

	void SetRendererMode(int mode, float alpha);
	void SetTexture(Texture texture, float offssetX, float offsetY);
	void SetTransform(const glm::mat4& modelMat);
};