#include "Camera.h"

glm::vec3	campos;
glm::vec3	camdir;
glm::vec3	camup;
float		camzoom;
float		camdegree;
glm::mat4	viewMatrix;
glm::mat4	projectionMatrix;

void CameraInit(glm::vec3 camPos, glm::vec3 camDir, glm::vec3 camUp, float camZoom, float camDegree)
{
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGTH;

	SetCamPos(camPos);
	SetCamDir(camDir);
	SetCamUp(camUp);
	SetCamZoom(camZoom);
	camdegree = camDegree;
	SetProjectionMat(GetCamZoom());
	SetViewMatrix(GetCamPos(), GetCamDir(), GetCamUp());
}

/* --------------------------------------Cam Properties Getters and Setters-------------------------------------- */
void SetCamPos(glm::vec3 pos)
{
	campos = pos;
}
void SetCamDir(glm::vec3 dir)
{
	camdir = dir;
}
void SetCamUp(glm::vec3 up)
{
	camup = up;
}
void SetCamZoom(float zoom)
{
	camzoom = zoom;
}

glm::vec3 GetCamPos()
{
	return campos;
}
glm::vec3 GetCamDir()
{
	return camdir;
}
glm::vec3 GetCamUp()
{
	return camup;
}
float GetCamZoom()
{
	return camzoom;
}
/* --------------------------------------Cam Properties Getters and Setters-------------------------------------- */

/* --------------------------------------Set position and zoom-------------------------------------- */
void MoveCamera(glm::vec3 moveVec)
{
	campos.x += moveVec.x;
	campos.y += moveVec.y;

	SetCamPosition(glm::vec3(GetCamPos()));
}
void CamZoomIn(float zoomFactor)
{
	float zoomAmount = GetCamZoom() - zoomFactor;
	SetCameraZoom(zoomAmount);
}
void CamZoomOut(float zoomFactor)
{
	CamZoomIn(-zoomFactor);
}
void SetCamPosition(glm::vec3 camPos)
{
	SetViewMatrix(camPos, GetCamDir(), GetCamUp());
}
void SetCameraZoom(float zoomFactor)
{
	SetCamZoom(zoomFactor);
	if (GetCamZoom() < 0.1f) { SetCamZoom(0.1f); }
	SetProjectionMat(GetCamZoom());
	SetViewMatrix(GetCamPos(), GetCamDir(), GetCamUp());
}
/* --------------------------------------Set position and zoom-------------------------------------- */

/* --------------------------------------Cam Matrix Properties Getters and Setters-------------------------------------- */
void SetViewMatrix(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	viewMatrix = glm::lookAt(pos, pos + dir, up);
}
void SetProjectionMat(float zoomFactor)
{
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGTH;

	projectionMatrix = glm::ortho(-(width / 2) * zoomFactor, (width / 2) * zoomFactor, -(height / 2) * zoomFactor, (height / 2) * zoomFactor, -20.0f, 20.0f);
}
glm::mat4 GetViewMatrix()
{
	return viewMatrix;
}
glm::mat4 GetProjectionMat()
{
	return projectionMatrix;
}
/* --------------------------------------Cam Matrix Properties Getters and Setters-------------------------------------- */