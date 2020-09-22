#include "TestRender.h"

#define COLOR_MODE 0
#define TEXTURE_MODE 1

Texture		testTex;

Mesh		testMesh;

void GameStateLevel1Load(void) 
{
	std::vector<Vertex> vertices;
	Vertex v1, v2, v3, v4;

	vertices.clear();
	v1.SetPosition(glm::vec3(-0.5f, -0.5f, 0.0f)); v1.SetColor(glm::vec3(1.0f, 0.0f, 0.0f)); v1.SetTexCoords(glm::vec2(0.0f, 0.0f));
	v2.SetPosition(glm::vec3( 0.5f, -0.5f, 0.0f)); v2.SetColor(glm::vec3(0.0f, 1.0f, 0.0f)); v2.SetTexCoords(glm::vec2(1.0f, 0.0f));
	v3.SetPosition(glm::vec3( 0.5f,  0.5f, 0.0f)); v3.SetColor(glm::vec3(0.0f, 0.0f, 1.0f)); v3.SetTexCoords(glm::vec2(1.0f, 1.0f));
	v4.SetPosition(glm::vec3(-0.5f,  0.5f, 0.0f)); v4.SetColor(glm::vec3(1.0f, 1.0f, 0.0f)); v4.SetTexCoords(glm::vec2(0.0f, 1.0f));

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v1);
	vertices.push_back(v3);
	vertices.push_back(v4);

	testMesh = LoadMesh(vertices);

	testTex = LoadTexture("blank.png");

	std::cout << "State Loaded" << std::endl;
}
void GameStateLevel1Init(void) 
{
	testMesh.modelMatrix = glm::translate(testMesh.modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	testMesh.modelMatrix = glm::scale(testMesh.modelMatrix, glm::vec3(100.0f, 100.0f, 1.0f));

	std::cout << "State Initialized" << std::endl;
}
void GameStateLevel1Update(double dt, long frame, int& state) 
{
	
}
void GameStateLevel1Draw(void)
{
	glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetRendererMode(TEXTURE_MODE, 1.0f);
	SetTexture(testTex, 0.0f, 0.0f);
	SetTransform(testMesh.modelMatrix);
	DrawMesh(testMesh);

	glfwSwapBuffers(window);

	//std::cout << "State Draw" << std::endl;
}
void GameStateLevel1Free(void) 
{
	testMesh.modelMatrix = glm::mat4(1.0f);

	std::cout << "State Freed" << std::endl;
}
void GameStateLevel1Unload(void) 
{
	UnloadMesh(testMesh);
	UnloadTexture(testTex);

	std::cout << "State Unloaded" << std::endl;
}