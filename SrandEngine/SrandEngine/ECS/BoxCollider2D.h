#pragma once

#include <string>

#include "GameObject.h"
#include "Component.h"
#include "RigidBody.h"
#include "Source/AssetManager.h"
#include "Source/Camera.h"

using namespace Srand;

class BoxCollider2D : public Component{
public:
	enum CollisionTag {
		COLLISION_START = 0,
		TILE_COLLISION,
		CHARACTER_COLLISION,
		DOOR_COLLISION,
		ELEVATOR_COLLISION,
		ASSET_COLLISION,
		BUTTON_COLLISION,
		GOAL_COLLISION,
		COLLISION_END
	};
	bool isHardCollide = false;
	bool iscarried = false;
private:
	friend class Collision;
	float width, height;
	CollisionTag tag = COLLISION_START;
	Transform* transform = nullptr;
	RigidBody* rigidBody = nullptr;

	bool allowOverlap = false;
	bool movable = false;

	std::string meshID = "";
	Mesh* mesh = nullptr;
	Camera* camera;

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	bool isGround;
	
	Vector2D_float modifyPosition;

public:
	BoxCollider2D(CollisionTag tag, float width, float height, bool overlap = false, bool movable = false, std::string meshID = "", Camera* camera = nullptr)
		: tag(tag), width(width), height(height), allowOverlap(overlap), movable(movable), meshID(meshID), camera(camera) {}

	BoxCollider2D(float width, float height, bool overlap = false, bool movable = false, std::string meshID = "", Camera* camera = nullptr)
		: width(width), height(height), allowOverlap(overlap), movable(movable), meshID(meshID), camera(camera) {}

	void SetOverlap(bool overlap) { allowOverlap = overlap; }

	void SetIsGround(bool isGround) { this->isGround = isGround; }
	bool GetIsGround() { return isGround; }

	int GetTag() { return tag; }
	bool GetOverlap() { return allowOverlap; }

	float GetWidth() { return width; }
	float GetHeight() { return height; }

	void SetOffset(float offsetX, float offsetY) {
		BoxCollider2D::offsetX = offsetX;
		BoxCollider2D::offsetY = offsetY;
	}

	bool Init() override final {
		transform = &gameObject->GetComponent<Transform>();
		if (meshID != "") {
			mesh = AssetManager::get().GetMesh(meshID);
		}

		modifyPosition = Vector2D_float(transform->position.x + offsetX, transform->position.y + offsetY);
		return true;
	}

	void Update() override final {
		isHardCollide = false;
		modifyPosition = Vector2D_float(transform->position.x + offsetX, transform->position.y + offsetY);
	}

	void Draw() override final {
		if (mesh != nullptr && camera != nullptr) {
			glUseProgram(Shader::get()->shader);

			//Set the render mode between Texture and Solid Color						// glGetUniformLocation called every frame is not efficient
			glUniform1i(glGetUniformLocation(Shader::get()->shader, "mode"), 0);
			glUniform1f(glGetUniformLocation(Shader::get()->shader, "alpha"), 1.0f);

			/*Set transform of the objects relative to camera*/
			// If there's no changing in scale and rotate on run time, move the modelMat to Init() and only calculate position here.
			glm::mat4 modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, glm::vec3(modifyPosition.x, modifyPosition.y, 0));
			modelMat = glm::scale(modelMat, glm::vec3(width, height, 1));
			modelMat = glm::rotate(modelMat, transform->rotationAngle * 3.14f / 180.0f, glm::vec3(0, 0, 1) /* rotate z-axis */);
			glm::mat4 MVP = camera->GetProjectionMat() * camera->GetViewMatrix() * modelMat;
			glUniformMatrix4fv(glGetUniformLocation(Shader::get()->shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);

			// Draw using mesh
			glBindVertexArray(mesh->vao);
			glDrawArrays(GL_LINE_LOOP, 0, mesh->vertex.size());

			glBindVertexArray(0);
		}
	}
};