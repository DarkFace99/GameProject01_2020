#include "TestRender.h"
#include "GameObject.h"
#define COLOR_MODE 0
#define TEXTURE_MODE 1

extern Mesh			meshArray[MAX_MESH];							// Store all unique shape/mesh in your game
extern int			numMesh;
extern Texture		texArray[MAX_TEXTURE];							// Corresponding texture of the mesh
extern int			numTex;
extern GameObject	gameObjectInstance_Array[MAX_INSTANCE_GAMEOBJECTS];			// Store all game object instance
extern int			numGameObj;

Texture		testTex;
Mesh		testMesh;

/* Test object */
GameObject* testGameObject;

void GameStateLevel1Load(void) 
{
	/* for assign value in meshArray & texArray */
	Mesh* meshPtr;
	Texture* texPtr;

		/* Test gameObject here */

	// clear the Mesh array
	memset(meshArray, 0, sizeof(Mesh) * MAX_MESH);
	numMesh = 0;

	// clear the Texture array
	memset(texArray, 0, sizeof(Texture) * MAX_TEXTURE);
	numTex = 0;

	// clear the game object instance array
	memset(gameObjectInstance_Array, 0, sizeof(GameObject) * MAX_INSTANCE_GAMEOBJECTS);
	numGameObj = 0;

	// Set the object instance to NULL
	//testGameObject = nullptr;

		/* Test gameObject end */

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
	testTex = LoadTexture("Assets/blank.png");

	/* Point array to slot of the test GameObject mesh & array according to TYPE */
	meshPtr = meshArray + TEST;
	texPtr = texArray + TEST;
	/* Assign value */
	*meshPtr = LoadMesh(vertices);
	*texPtr = LoadTexture("Assets/blank.png");

	std::cout << "State Loaded" << std::endl;
}
void GameStateLevel1Init(void) 
{
	testMesh.modelMatrix = glm::translate(testMesh.modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	testMesh.modelMatrix = glm::scale(testMesh.modelMatrix, glm::vec3(100.0f, 100.0f, 1.0f));

	/* Test gameObject here */

	testGameObject = GameObject::GameObject_Instance_CREATE(TEST, glm::vec3(100.0f, 100.0f, 0.0f), glm::vec3(150.0f, 150.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, OUT_CONTROLLED);

	/* Test gameObject end */

	std::cout << "State Initialized" << std::endl;
}
void GameStateLevel1Update(double dt, long frame, int& state) 
{
	
}
void GameStateLevel1Draw(void)
{
	glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	SetRendererMode(TEXTURE_MODE, 1.0f);
	SetTexture(testTex, 0.0f, 0.0f);
	SetTransform(testMesh.modelMatrix);
	DrawMesh(testMesh);
	*/

	/* Test gameObject here */

	// draw all game object instance in the sGameObjInstArray
	for (int i = 0; i < MAX_INSTANCE_GAMEOBJECTS; i++) {
		GameObject* instPtr = gameObjectInstance_Array + i;
		
		// skip inactive object
		if (instPtr->GetFlag() == FLAG_INACTIVE_GAMEOBJECT)
			continue;

		// 4 steps to draw sprites on the screen
		//	1. SetRenderMode()
		//	2. SetTexture()
		//	3. SetTransform()
		//	4. DrawMesh()

		SetRendererMode(TEXTURE_MODE, 1.0f);
		SetTexture(*instPtr->GetTexture(), 0.0f, 0.0f);
		SetTransform(instPtr->GetModelMatrix());
		DrawMesh(*instPtr->GetMesh());
		//std::cout << "Texture: " <<*instPtr->GetTexture() << std::endl;
		//std::cout << "ModelMat: " << glm::to_string(instPtr->GetModelMatrix()) << std::endl;

		/* Test gameObject end */
	}

	glfwSwapBuffers(window);

	//std::cout << "State Draw" << std::endl;
}
void GameStateLevel1Free(void) 
{
	testMesh.modelMatrix = glm::mat4(1.0f);

	// call GameObject_Instance_DESTROY for all object instances in the gameObjectInstance_Array
	for (int i = 0; i < MAX_INSTANCE_GAMEOBJECTS; i++) {
		GameObject::GameObject_Instance_DESTROY(gameObjectInstance_Array[i]);
	}

	std::cout << "State Freed" << std::endl;
}
void GameStateLevel1Unload(void) 
{
	UnloadMesh(testMesh);
	UnloadTexture(testTex);

	// Unload all meshes in MeshArray
	for (int i = 0; i < MAX_MESH; i++) {
		UnloadMesh(meshArray[i]);
	}

	// Unload all textures in TexArray
	for (int i = 0; i < MAX_TEXTURE; i++) {
		UnloadTexture(texArray[i]);
	}

	std::cout << "State Unloaded" << std::endl;
}