#pragma once

/* Custom Header */
#include "Source/Engine.h"
#include "GameObject.h"
#include "Component.h"
#include "Source/AssetManager.h"
#include "Source/Camera.h"

// for checking glm::mat
#include <gtx/string_cast.hpp>

using namespace Srand;

class SpriteRenderer : public Component {
public:
	enum LayerTag {
		LAYER_START = 0,
		TILE_LAYER,
		CHARACTER_LAYER,
		ASSET_LAYER,
		LAYER_END
	};

private:

	Transform* transform = nullptr;
	std::string textureID = "";
	std::string meshID = "";

	Texture* texture = nullptr;
	Mesh* mesh = nullptr;
	float alpha = 1;
	bool flip = false;

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	Camera* camera;

	LayerTag tag = LAYER_START;
	
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;

	float* GetOffSetX() {
		return &offsetX;
	}

	float* GetOffSetY() {
		return &offsetY;
	}

	void SetFlip(bool condition) { flip = condition; }
	void SetAlpha(float alpha) { this->alpha = alpha; }

	SpriteRenderer(std::string meshID, std::string textureID, float alpha, Camera* camera, bool flip)
		: meshID(meshID), textureID(textureID), alpha(alpha), camera(camera), flip(flip){
		/*std::cout << "Create Sprite Renderer: " << std::endl;
		std::cout << "meshID: " <<meshID << std::endl;
		std::cout << "textureID: " << textureID << std::endl;
		std::cout << "alpha: " << alpha << std::endl;*/
	}

	SpriteRenderer(LayerTag tag, std::string meshID, std::string textureID, float alpha, Camera* camera, bool flip)
		: tag(tag), meshID(meshID), textureID(textureID), alpha(alpha), camera(camera), flip(flip) {}

	int GetTag() { return tag; }

	bool Init() override final {
		transform = &gameObject->GetComponent<Transform>();			
		texture = AssetManager::get().GetTexture(textureID);
		mesh = AssetManager::get().GetMesh(meshID);

		//std::cout << "Sprite: texture load " << *texture << std::endl;
		//std::cout << "Sprite: mesh load " << mesh << std::endl;

		return true;
	}

	void Draw() override final {

		// Set the viewport of the screen. Lower Left coner will be (0,0) and the dimension will be SCREEN_WIDTH and SCREEN_HEIGTH
		glViewport(0, 0, WindowProperties::get().GetWidth(), WindowProperties::get().GetHeight());
		glUseProgram(Shader::get()->shader);

		//Set the render mode between Texture and Solid Color						// glGetUniformLocation called every frame is not efficient
		glUniform1i(glGetUniformLocation(Shader::get()->shader, "mode"), 1);
		glUniform1f(glGetUniformLocation(Shader::get()->shader, "alpha"), alpha);

		glUniform1f(glGetUniformLocation(Shader::get()->shader, "offsetX"), offsetX);
		glUniform1f(glGetUniformLocation(Shader::get()->shader, "offsetY"), offsetY);

		// Set texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glUniform1i(glGetUniformLocation(Shader::get()->shader, "tex1"), 0);

		/*Set transform of the objects relative to camera*/		
		// If there's no changing in scale and rotate on run time, move the modelMat to Init() and only calculate position here.
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat, glm::vec3(transform->position.x, transform->position.y,0));
		modelMat = glm::scale(modelMat, glm::vec3((flip) ? -transform->scale.x : transform->scale.x, transform->scale.y,1));
		modelMat = glm::rotate(modelMat, transform->rotationAngle * 3.14f / 180.0f, glm::vec3(0, 0, 1) /* rotate z-axis */ );
		glm::mat4 MVP = camera->GetProjectionMat() * camera->GetViewMatrix() * modelMat;
		glUniformMatrix4fv(glGetUniformLocation(Shader::get()->shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);

		// Draw using mesh
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertex.size());

		glBindVertexArray(0);
	}

	void Update() override final {
		/*transform = &gameObject->GetComponent<Transform>();*/
	}

};