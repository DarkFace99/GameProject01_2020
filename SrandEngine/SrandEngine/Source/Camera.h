#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/random.hpp>

#include "System.h"

	/* Parameter List: CamPos, CamDir, CamUp, camZoom, CamDegree*/
	void CameraInit(glm::vec3 camPos, glm::vec3 camDir, glm::vec3 camUp, float camZoom, float camDegree);

	/* ---------Cam Properties Getters and Setters--------- */
	void		SetCamPos(glm::vec3 pos);
	void		SetCamDir(glm::vec3 dir);
	void		SetCamUp(glm::vec3 up);
	void		SetCamZoom(float zoom);

	glm::vec3	GetCamPos();
	glm::vec3	GetCamDir();
	glm::vec3	GetCamUp();
	float		GetCamZoom();
	/* ---------Cam Properties Getters and Setters--------- */

	/* ---------Set position and zoom--------- */
	void		MoveCamera(glm::vec3 moveVec);
	void		CamZoomIn(float zoomFactor);
	void		CamZoomOut(float zoomFactor);
	void		SetCamPosition(glm::vec3 camPos);
	void		SetCameraZoom(float zoomFactor);
	/* ---------Set position and zoom--------- */

	/* ---------Cam Matrix Properties Getters and Setters--------- */
	void		SetViewMatrix(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	void		SetProjectionMat(float zoomFactor);
	glm::mat4	GetViewMatrix();
	glm::mat4	GetProjectionMat();
	/* ---------Cam Matrix Properties Getters and Setters--------- */
