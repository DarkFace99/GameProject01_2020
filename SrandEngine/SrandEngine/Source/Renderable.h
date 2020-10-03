#pragma once

#include <GL/glew.h>
#include <GLM.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/random.hpp>
#include <vector>
#include <time.h>

/* Custom Header */
#include "System.h"
#include "Shader.h"
#include "SOIL.h"
#include "Camera.h"


/* Typdef for Texture */
typedef GLuint Texture;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


/*Global for all use*/

//-----------------------------------------


/* Vertex class declaration */
class Vertex {
protected:

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

	std::vector<float> GetDataArray();

	glm::vec3 position;		// x, y, z
	glm::vec3 color;		// r, g, b
	glm::vec2 texCoords;	// u, v

};

/* Mesh class declaration */
class Mesh {
public:
	GLuint vao; // vertex array object
	GLuint vertexBuffer;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	std::vector<Vertex> vertex;
};

/* Renderable class declaration */
void RendererInit();

/*------------------- Texture Function -------------------*/
Texture LoadTexture(const char* filename);
void UnloadTexture(Texture texture);

/*------------------- Mesh Function -------------------*/
Mesh LoadMesh(std::vector<Vertex> in_vertex);
void DrawMesh(Mesh mesh);
void UnloadMesh(Mesh mesh);

/*-------------------Set Renderer Function-------------------*/
void SetRendererMode(int mode, float alpha);
void SetTexture(Texture texture, float offssetX, float offsetY);
void SetTransform(const glm::mat4& modelMat);
