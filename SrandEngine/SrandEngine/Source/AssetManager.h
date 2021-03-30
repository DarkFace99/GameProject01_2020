#pragma once

#include <srpch.h>

/* Custom Header */
#include "Mesh.h"
#include "SOIL.h"

#include "Shader.h"
#include "Engine.h"

#define ASSET_FILE_PATH "Assets/"

/* Typdef for Texture */
typedef GLuint Texture;

namespace Srand
{
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
		void LoadTexture(std::string id, std::string filename);

		Mesh* GetMesh(std::string id);
		void LoadMesh(std::string id, int frameCountX = 1, int frameCountY = 1, int frameSpaceX = 1, int frameSpaceY = 1);

		/* singleton */
		inline static AssetManager& get() {
			if (s_instance == nullptr) {
				s_instance = new AssetManager();
			}
			return *s_instance;
		}
	};
}
