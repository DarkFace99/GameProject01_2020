#pragma once

/* Custom Header */
#include "GameObject.h"
#include "Component.h"
#include "AssetManager.h"
#include "Shader.h"

class SpriteRenderer : public Component {
private:

	Transform* transform;
	std::string textureID = "";
	std::string meshID = "";

	Texture* texture;
	Mesh* mesh;
	int mode;
	float alpha;
	bool flip = false;
	
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;

	SpriteRenderer(std::string meshID, std::string textureID, int mode, float alpha) 
		: meshID(meshID), textureID(textureID), mode(mode), alpha(alpha) {}

	bool Init() override final {
		transform = &gameObject->GetComponent<Transform>();
		texture = AssetManager::get().GetTexture(textureID);
		mesh = AssetManager::get().GetMesh(meshID);
	}

	void Draw() override final {
		
		// Set the viewport of the screen. Lower Left coner will be (0,0) and the dimension will be SCREEN_WIDTH and SCREEN_HEIGTH
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGTH);
		glUseProgram(shader);

		//Set the render mode between Texture and Solid Color
		glUniform1i(glGetUniformLocation(shader, "mode"), mode);
		glUniform1f(glGetUniformLocation(shader, "alpha"), alpha);

		glUniform1f(glGetUniformLocation(shader, "offsetX"), 0.0f);
		glUniform1f(glGetUniformLocation(shader, "offsetY"), 0.0f);

		// Set texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glUniform1i(glGetUniformLocation(shader, "tex1"), 0);

		/*Set transform of the objects relative to camera*/


		// Draw using mesh
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertex.size());

		glBindVertexArray(0);
	}

	void Update() override final {
		transform = &gameObject->GetComponent<Transform>();
	}

};