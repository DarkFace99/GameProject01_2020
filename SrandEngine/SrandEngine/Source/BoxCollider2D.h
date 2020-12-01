#pragma once

#include <string>

#include "GameObject.h"
#include "Component.h"
#include "AssetManager.h"
#include "Camera.h"

class BoxCollider2D : public Component{
private:
	friend class Collision;
	float width, height;
	std::string collisionTag = "";
	Transform* transform = nullptr;

	bool allowOverlap = false;
	bool movable = false;

	std::string meshID = "";
	Mesh* mesh = nullptr;
	Camera* camera;

public:
	BoxCollider2D(std::string tag, float width, float height, std::string meshID, Camera* camera, bool overlap = false, bool movable = false)
		: collisionTag(tag), width(width), height(height), meshID(meshID), camera(camera), allowOverlap(overlap), movable(movable){}

	BoxCollider2D(float width, float height, std::string meshID, Camera* camera, bool overlap = false, bool movable = false)
		: width(width), height(height), meshID(meshID), camera(camera), allowOverlap(overlap), movable(movable){}

	std::string GetTag() { return collisionTag; }

	bool Init() override final {
		transform = &gameObject->GetComponent<Transform>();
		mesh = AssetManager::get().GetMesh(meshID);
		return true;
	}

	void Update() override final {
	}

	void Draw() override final {
		glUseProgram(Shader::get()->shader);

		//Set the render mode between Texture and Solid Color						// glGetUniformLocation called every frame is not efficient
		glUniform1i(glGetUniformLocation(Shader::get()->shader, "mode"), 0);
		glUniform1f(glGetUniformLocation(Shader::get()->shader, "alpha"), 1.0f);

		/*Set transform of the objects relative to camera*/
		// If there's no changing in scale and rotate on run time, move the modelMat to Init() and only calculate position here.
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat, glm::vec3(transform->position.x, transform->position.y, 0));
		modelMat = glm::scale(modelMat, glm::vec3(transform->scale.x, transform->scale.y, 1));
		modelMat = glm::rotate(modelMat, transform->rotationAngle * 3.14f / 180.0f, glm::vec3(0, 0, 1) /* rotate z-axis */);
		glm::mat4 MVP = camera->GetProjectionMat() * camera->GetViewMatrix() * modelMat;
		glUniformMatrix4fv(glGetUniformLocation(Shader::get()->shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);

		// Draw using mesh
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_LINE_LOOP, 0, mesh->vertex.size());

		glBindVertexArray(0);
	}
};