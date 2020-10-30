#pragma once

#include <map>
#include <string>
#include <iostream>

/* Custom Header */
#include "Engine.h"
#include "Mesh.h"
#include "SOIL.h" 


/* Typdef for Texture */
typedef GLuint Texture;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class AssetManager {
private:
	static AssetManager* s_instance;
	std::map<std::string, Texture*> textures;
	std::map<std::string, Mesh*> meshes;

public:
	AssetManager() = default;
	~AssetManager() = default;

	void Clean();

	Texture* GetTexture(std::string id);
	void LoadTexture(std::string id, const char* filename);

	Mesh* GetMesh(std::string id);
	void LoadMesh(std::string id, int frameCount);

	/* singleton */
	inline static AssetManager& get() {
		if (s_instance == nullptr) {
			s_instance = new AssetManager();
		}
		return *s_instance;
	}
};
