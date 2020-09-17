#pragma once

#include <GL/glew.h>
#include <GLM.hpp>
#include <vector>

/*Custom Header*/
#include "System.h"
#include "Shader.h"


/* Typdef for Texture */
typedef GLuint Texture;


/*Global for all use*/
extern unsigned int		shader;
glm::mat4				MVP;
Texture					blankTex;

//Camera-----------------------------------
glm::vec3				campos;
glm::vec3				camdir;
glm::vec3				camup;
float					camzoom;
float					camdegree;
glm::mat4				viewMatrix;
glm::mat4				projectionMatrix;
//-----------------------------------------


/* Vertex class declaration */
class Vertex {
protected:
	glm::vec3 position;		// x, y, z
	glm::vec3 color;		// r, g, b
	glm::vec2 texCoords;	// u, v

public:
	Vertex();
	Vertex( glm::vec3 position, glm::vec3 color, glm::vec2 textureCoordinate);
	void setPositionX(float x);
	void setPositionY(float y);
	void setPositionZ(float z);
	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();

	void SetColorR(float r);
	void SetColorG(float g);
	void SetColorB(float b);
	void SetColor(glm::vec3 color);
	glm::vec3 GetColor();

	void SetTexCoordsU(float u);
	void SetTexCoordsV(float v);
	void SetTexCoords(glm::vec2 TexCoords);
	glm::vec2 GetTexCoords();
};

/* Mesh class declaration */
class Mesh {
public:
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

	Mesh LoadMesh(std::vector<Vertex> in_vertex);
	void DrawMesh(Mesh mesh);
	void UnloadMesh(Mesh mesh);

	/*-------------------Set Renderer Function-------------------*/
	void SetRendererMode(int mode, float alpha);
	void SetTexture(Texture texture, float offssetX, float offsetY);
	void SetTransform(const glm::mat4& modelMat);
};