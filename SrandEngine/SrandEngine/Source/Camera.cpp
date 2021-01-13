#include "Camera.h"

namespace Srand
{
	Camera::Camera(glm::vec3 camPos, glm::vec3 camDir, glm::vec3 camUp, float camZoom, float camDegree)
	{
		SetCamPos(camPos);
		SetCamDir(camDir);
		SetCamUp(camUp);
		SetCamZoom(camZoom);
		Camera::camDegree = camDegree;
		SetProjectionMat();
		SetViewMatrix();
	}
	Camera::~Camera()
	{

	}

	void Camera::SetCamPos(glm::vec3 camPos)
	{
		Camera::camPosition = camPos;
	}
	void Camera::SetCamDir(glm::vec3 camDir)
	{
		Camera::camDirection = camDir;
	}
	void Camera::SetCamUp(glm::vec3 camUp)
	{
		Camera::camUp = camUp;
	}
	void Camera::SetCamZoom(float camZoom)
	{
		Camera::camZoom = camZoom;
	}
	glm::vec3 Camera::GetCamPos()
	{
		return camPosition;
	}
	float Camera::GetCamPosX()
	{
		return camPosition.x;
	}
	float Camera::GetCamPosY()
	{
		return camPosition.y;
	}
	float Camera::GetCamPosZ()
	{
		return camPosition.z;
	}
	glm::vec3 Camera::GetCamDir()
	{
		return camDirection;
	}
	glm::vec3 Camera::GetCamUp()
	{
		return camUp;
	}
	float Camera::GetCamZoom()
	{
		return camZoom;
	}

	void Camera::MoveCamera(glm::vec3 moveVec)
	{
		float tempX = GetCamPosX();
		float tempY = GetCamPosY();
		float tempZ = GetCamPosZ();

		tempX += moveVec.x;
		tempY += moveVec.y;
		tempZ += moveVec.z;

		SetCamPos(glm::vec3(tempX, tempY, tempZ));

		SetViewMatrix();
	}
	void Camera::CamZoomIn(float zoomFactor)
	{
		float zoomAmount = GetCamZoom() - zoomFactor;
		SetCameraZoom(zoomAmount);
	}
	void Camera::CamZoomOut(float zoomFactor)
	{
		CamZoomIn(-zoomFactor);
	}
	//void Camera::SetCamPosition()
	//{
	//	SetViewMatrix();
	//}
	void Camera::SetCameraZoom(float zoomFactor)
	{
		SetCamZoom(zoomFactor);
		if (GetCamZoom() < 0.1f) { SetCamZoom(0.1f); }
		SetProjectionMat();
		SetViewMatrix();
	}

	void Camera::SetViewMatrix()
	{
		Camera::viewMatrix = glm::lookAt(GetCamPos(), GetCamPos() + GetCamDir(), GetCamUp());
	}
	void Camera::SetProjectionMat()
	{
		//int width = SCREEN_WIDTH;	//Need to use global Variable from system
		//int height = SCREEN_HEIGTH;	//Need to use global Variable from system

		Camera::projectionMatrix = glm::ortho(-(SCREEN_WIDTH / 2) * GetCamZoom(), (SCREEN_WIDTH / 2) * GetCamZoom(),
			-(SCREEN_HEIGTH / 2) * GetCamZoom(), (SCREEN_HEIGTH / 2) * GetCamZoom(),
			-20.0f, 20.0f);
	}
	glm::mat4 Camera::GetViewMatrix()
	{
		return viewMatrix;
	}
	glm::mat4 Camera::GetProjectionMat()
	{
		return projectionMatrix;
	}
}
