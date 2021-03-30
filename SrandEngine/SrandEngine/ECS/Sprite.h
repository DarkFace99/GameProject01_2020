#pragma once

/* Custom Header */
#include "GameObject.h"
#include "Component.h"
#include "Source/AssetManager.h"

class Sprite : public Component{
private:
	std::string meshID = "";
	std::string textureID = "";
	
	Transform* transform;
	Mesh* mesh;
	Texture* texture;
	float alpha;
	bool flip = false;
	
public:
	Sprite(std::string meshID, std::string textureID, float alpha) : meshID(meshID), textureID(textureID), alpha(alpha) {
		transform = &gameObject->GetComponent<Transform>();
		mesh = AssetManager::get().GetMesh(meshID);
		texture = AssetManager::get().GetTexture(textureID);
	}
};
