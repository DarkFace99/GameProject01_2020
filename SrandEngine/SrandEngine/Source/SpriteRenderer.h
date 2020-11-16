#pragma once

/* Custom Header */
#include "GameObject.h"
#include "Component.h"
#include "AssetManager.h"
#include "Camera.h"

// for checking glm::mat
#include <gtx/string_cast.hpp>

class SpriteRenderer : public Component {
private:

	Transform* transform;
	std::string textureID = "";
	std::string meshID = "";

	Texture* texture;
	Mesh* mesh;
	float alpha;
	bool flip = false;

	Camera camera;
	
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;

	SpriteRenderer(std::string meshID, std::string textureID, float alpha, Camera &camera) 
		: meshID(meshID), textureID(textureID), alpha(alpha), camera(camera){
		std::cout << "Create Sprite Renderer: " << std::endl;
		std::cout << "meshID: " <<meshID << std::endl;
		std::cout << "textureID: " << textureID << std::endl;
		std::cout << "alpha: " << alpha << std::endl;
	}

	bool Init() override final {
		/*transform = &gameObject->GetComponent<Transform>();*/			// problem !!
		texture = AssetManager::get().GetTexture(textureID);
		mesh = AssetManager::get().GetMesh(meshID);

		std::cout << "Sprite: texture load " << texture << std::endl;
		std::cout << "Sprite: mesh load " << mesh << std::endl;

		/*for (std::vector<Vertex>::const_iterator i = mesh->vertex.begin(); i < mesh->vertex.end(); ++i){
			std::cout << "position: " << glm::to_string(i->position) << " color: " << glm::to_string(i->color) << " texCoords: " << glm::to_string(i->texCoords) << std::endl << std::endl;
		}*/
		return true;
	}

	void Draw() override final {

		std::cout << Shader::get()->shader << std::endl;

		// Set the viewport of the screen. Lower Left coner will be (0,0) and the dimension will be SCREEN_WIDTH and SCREEN_HEIGTH
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGTH);
		glUseProgram(Shader::get()->shader);

		//Set the render mode between Texture and Solid Color
		glUniform1i(glGetUniformLocation(Shader::get()->shader, "mode"), 0);
		glUniform1f(glGetUniformLocation(Shader::get()->shader, "alpha"), alpha);

		glUniform1f(glGetUniformLocation(Shader::get()->shader, "offsetX"), 0.0f);
		glUniform1f(glGetUniformLocation(Shader::get()->shader, "offsetY"), 0.0f);

		// Set texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glUniform1i(glGetUniformLocation(Shader::get()->shader, "tex1"), 0);

		/*Set transform of the objects relative to camera*/
		glm::mat4 modelMat = glm::mat4(1.0f);
		/*std::cout << std::endl << "Camera:" << std::endl;
		std::cout << "modelMat_Origin: " << glm::to_string(modelMat) << std::endl << std::endl;*/
		modelMat = glm::translate(modelMat, glm::vec3(transform->position.x, transform->position.y,0));
		/*std::cout << "translate: " << transform->position << std::endl;
		std::cout << "modelMat_translate: " << glm::to_string(modelMat) << std::endl << std::endl;*/
		modelMat = glm::scale(modelMat, glm::vec3(transform->scale.x, transform->scale.y,1));
		/*std::cout << "scale: " << transform->scale << std::endl;
		std::cout << "modelMat_scale: " << glm::to_string(modelMat) << std::endl << std::endl;*/
		modelMat = glm::rotate(modelMat, transform->rotationAngle * 3.14f / 180.0f, glm::vec3(0, 0, 1) /* rotate z-axis */ );
		/*std::cout << "rotate: " << transform->rotationAngle << std::endl;
		std::cout << "modelMat_rotate: " << glm::to_string(modelMat) << std::endl << std::endl;*/
		glm::mat4 MVP = camera.GetProjectionMat() * camera.GetViewMatrix() * modelMat;
		glUniformMatrix4fv(glGetUniformLocation(Shader::get()->shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
		/*std::cout << std::endl << std::endl;
		std::cout << "modelMat: " << glm::to_string(modelMat) << std::endl << std::endl;
		std::cout << "ProjectionMat: " << glm::to_string(camera.GetProjectionMat()) << std::endl << std::endl;
		std::cout << "ViewMat: " << glm::to_string(camera.GetViewMatrix()) << std::endl << std::endl;
		std::cout << "MVP: " <<glm::to_string(MVP) << std::endl << std::endl;*/

		// Draw using mesh
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertex.size());

		glBindVertexArray(0);
	}

	void Update() override final {
		transform = &gameObject->GetComponent<Transform>();
	}

};