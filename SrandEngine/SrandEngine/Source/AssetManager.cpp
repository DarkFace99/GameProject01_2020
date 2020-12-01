#include "AssetManager.h"

// singleton
AssetManager* AssetManager::s_instance = nullptr;

void AssetManager::Clean() {
	
	// textures
	for (auto it = textures.begin(); it != textures.end(); ++it) {		
		delete it->second;
		/*textures.erase(it);*/											// problem!!
	}
	textures.clear();

	// meshes
	for (auto it = meshes.begin(); it != meshes.end(); it++) {			
		delete it->second;
		/*meshes.erase(it);*/											// problem!!
	}
	meshes.clear();
}

/*---------------------------------*/
/*		   Texture Function		   */	
/*---------------------------------*/

Texture* AssetManager::GetTexture(std::string id) {
	// check if id exists in container, then return according to the result
	if (textures.count(id) <= 0) { std::cout << "AssestManager: Cannot find texture " << id << std::endl; }
	else { std::cout << "AssestManager: Get texture " << id << std::endl; }
	return (textures.count(id) > 0) ? textures[id] : nullptr;
}

void AssetManager::LoadTexture(std::string id, const char* filename) {
	
	Texture* aTex = new Texture();

	GLubyte*	pData;
	int			texWidth, texHeight, channels;

	/* load texture using SOIL */
	pData = SOIL_load_image(filename, &texWidth, &texHeight, &channels, SOIL_LOAD_AUTO);

	if (pData == nullptr) { 
		std::cout << "texture: Cannot find texture [" << filename << "]" << std::endl;
		delete aTex;
		return;
	}

	glGenTextures(1, aTex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *aTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	GLint format = (channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, pData);

	SOIL_free_image_data(pData);

	/* store texture pointer to textures */
	if (aTex) {
		if (textures.count(id) <= 0) {
			textures[id] = aTex;
			std::cout << "texture: [" << filename << "] loaded!" << std::endl;
		}
		else {
			delete aTex;
			std::cout << "texture: //Error// id [" << id << "] was already used!" << std::endl;
		}
	}
	else { 
		delete aTex;
		std::cout << "texture: //Error// [" << filename << "] load failed!!" << std::endl; 
	}
}

/*---------------------------------*/
/*		   Mesh Function		   */
/*---------------------------------*/

Mesh* AssetManager::GetMesh(std::string id) {
	// check if id exists in container, then return according to the result
	if (meshes.count(id) <= 0) { std::cout << "Cannot find mesh " << id << std::endl; }
	else { std::cout << "AssestManager: Get texture " << id << std::endl; }
	return (meshes.count(id) > 0) ? meshes[id] : nullptr;
}

void AssetManager::LoadMesh(std::string id, int frameCount) {
	
	std::vector<Vertex> vertices;
	Vertex v1, v2, v3, v4;

	vertices.clear();
	v1.SetPosition(glm::vec3(-0.5f, -0.5f, 0.0f)); v1.SetColor(glm::vec3(1.0f, 0.0f, 0.0f)); v1.SetTexCoords(glm::vec2(0.0f, 0.0f));
	v2.SetPosition(glm::vec3(0.5f, -0.5f, 0.0f)); v2.SetColor(glm::vec3(0.0f, 1.0f, 0.0f)); v2.SetTexCoords(glm::vec2(1.0f/frameCount, 0.0f));
	v3.SetPosition(glm::vec3(0.5f, 0.5f, 0.0f)); v3.SetColor(glm::vec3(0.0f, 0.0f, 1.0f)); v3.SetTexCoords(glm::vec2(1.0f/frameCount, 1.0f));
	v4.SetPosition(glm::vec3(-0.5f, 0.5f, 0.0f)); v4.SetColor(glm::vec3(1.0f, 1.0f, 0.0f)); v4.SetTexCoords(glm::vec2(0.0f, 1.0f));

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v1);
	vertices.push_back(v3);
	vertices.push_back(v4);

	Mesh *aMesh = new Mesh();
	aMesh->vertex = vertices;

	std::vector<float> meshData;

	for (int i = 0; i < vertices.size(); i++)
	{
		std::vector<float> vertexData = vertices[i].GetDataArray();
		meshData.insert(meshData.end(), vertexData.begin(), vertexData.end());
	}

	glGenBuffers(1, &aMesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, aMesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshData.size(), &meshData[0], GL_STATIC_DRAW);

	/*Put in Mesh data to buffer*/
	glGenVertexArrays(1, &aMesh->vao);
	glBindVertexArray(aMesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, aMesh->vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));		//The starting point of the VBO, for the vertices
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(12));     //The starting point of color, 12 bytes away
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(24));

	glBindVertexArray(0);

	/* store mesh pointer to meshes */
	if (aMesh) {
		if (meshes.count(id) <= 0) {
			meshes[id] = aMesh;
			std::cout << "mesh: [" << id << "] Created!" << std::endl;
		}
		else {
			delete aMesh;
			std::cout << "mesh: //Error// id [" << id << "] was already used!" << std::endl;
		}
	}
	else {
		delete aMesh;
		std::cout << "mesh: //Error// [" << id << "] create failed!!" << std::endl; 
	}
}