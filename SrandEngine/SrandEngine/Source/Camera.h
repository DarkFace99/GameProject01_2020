#pragma once

/* Include C/C++ Headers */
#include <iostream>

/* Include GLMath Headers */
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/random.hpp>

#include "Engine.h"

class Camera 
{
private:
	glm::vec3	camPosition;		//Camera Position in World
	glm::vec3	camDirection;		//Direction that camera is facing
	glm::vec3	camUp;				//Up Vector of the camera
	float		camZoom;			//The amount of Zoom of the Camera
	float		camDegree;			//The amount of Rotation of the Camera
	glm::mat4	viewMatrix;			//Matrix to tell where the Camera is looking at
	glm::mat4	projectionMatrix;	//Matrix to set the Orthogornal Camera

public:
	/// <summary>
	///		Initialize Camera to Use In the Scene
	/// </summary>
	/// <param name="camPos"> : Camera Position to Initialize. </param>
	/// <param name="camDir"> : Direction that Camera is facing.  </param>
	/// <param name="camUp"> : Up Vector to Know the Camera Orientation. </param>
	/// <param name="camZoom"> : The Amount of Zoom Camera has. </param>
	/// <param name="camDegree"> : The Amount of Rotation Camera has. </param>
	Camera(glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 camDir = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f), float camZoom = 1.0f, float camDegree = 0.0f);
	/* Default Destructor */
	~Camera();

	/// <summary>
	///		Set Camera Position According to Parameter
	/// </summary>
	/// <param name="camPos"> : Position of Camera </param>
	void		SetCamPos(glm::vec3 camPos);

	/// <summary>
	///		Set Camera Direction According to Parameter
	/// </summary>
	/// <param name="camDir"> : Looking Direction of Camera </param>
	void		SetCamDir(glm::vec3 camDir);

	/// <summary>
	///		Set Camera Up Vector According to Parameter 
	/// </summary>
	/// <param name="camUp"> : Camera Up Vector </param>
	void		SetCamUp(glm::vec3 camUp);

	/// <summary>
	///		Set Camera Zoom According to Parameter
	/// </summary>
	/// <param name="camZoom"> : Camera Zoom Amount </param>
	void		SetCamZoom(float camZoom);


	/// <summary>
	///		Get Camera Current Position
	/// </summary>
	/// <returns> glm::vec3 : Camera Position </returns>
	glm::vec3	GetCamPos();
	float		GetCamPosX();
	float		GetCamPosY();

	/// <summary>
	///		Get Camera Current Direction
	/// </summary>
	/// <returns> glm::vec3 : Camera Direction </returns>
	glm::vec3	GetCamDir();

	/// <summary>
	///		Get Camera Current Up Vector
	/// </summary>
	/// <returns> glm::vec3 : Camera Up Vector </returns>
	glm::vec3	GetCamUp();

	/// <summary>
	///		Get Current Camera Zoom
	/// </summary>
	/// <returns> float : Camera Zoom </returns>
	float		GetCamZoom();

	
	/// <summary>
	///		Move Camera by Certain Value According to parameter
	/// </summary>
	/// <param name="moveVec"> : Vector to increment the Position </param>
	void		MoveCamera(glm::vec3 moveVec);

	/// <summary>
	///		Zoom Camera In by certain Value According to Parameter
	/// </summary>
	/// <param name="zoomFactor"> : Float Value to Increment the Zoom Value </param>
	void		CamZoomIn(float zoomFactor);

	/// <summary>
	///		Zoom Camera Out by certain Value According to Parameter
	/// </summary>
	/// <param name="zoomFactor"> : Float Value to Decrement the Zoom Value </param>
	void		CamZoomOut(float zoomFactor);

	/// <summary>
	///		Set Camera Position and Update to View Matrix
	/// </summary>
	/// <param name="camPos"> : Vec3 Value to set Camera Position </param>
	void		SetCamPosition(glm::vec3 camPos);

	/// <summary>
	///		Set Camera Zoom and Update to Projection Matrix
	/// </summary>
	/// <param name="zoomFactor"> : Float Value to set Camera Zoom </param>
	void		SetCameraZoom(float zoomFactor);

	
	/// <summary>
	///		Set Camera View Matrix
	/// </summary>
	void		SetViewMatrix();

	/// <summary>
	///		Set Camera Projection Matrix
	/// </summary>
	void		SetProjectionMat();

	/// <summary>
	///		Get Camera Current View Matrix
	/// </summary>
	/// <returns> glm::mat4 : Camera View Matrix </returns>
	glm::mat4	GetViewMatrix();

	/// <summary>
	///		Get Camera Current Projection Matrix
	/// </summary>
	/// <returns> glm::mat4 : Camera Projection Matrix </returns>
	glm::mat4	GetProjectionMat();

	void		ResetCamera();
};