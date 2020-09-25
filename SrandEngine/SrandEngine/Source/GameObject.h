#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLM.hpp>
#include <SOIL.h>
#include <vector>

#include "Renderable.h"


#define MAX_MESH					64				// The total number of Mesh (Shape)
#define MAX_TEXTURE					64				// The total number of texture
#define MAX_INSTANCE_GAMEOBJECTS	1024			// The total number of different game object instances

#define FLAG_ACTIVE_GAMEOBJECT					1
#define FLAG_INACTIVE_GAMEOBJECT				0



enum gameObject_TAG									// Tag for GameObjects
{													// range [-9, 10] 
	DEFAULT = 0,

	BG,				// Background

	PLATFORM,		// Object
	ELEMENT,

	NPC,			// Character
	BARTER,
	PEAR,
	CHERRY,
	MACHO,
	BENNY,

	UI,				// User Interface
	TEST			// for testing purpose
};



class GameObject 
{
private:
	Mesh*			mesh;
	Texture*		texture;

	int				tag;							// gameObject Tag
	int				flag;
	int				component_mode;					// Active or Inactive

	glm::vec3		position;						// For 2D use only X and Y, set Z to O
	glm::vec3		scale;							// For 2D use only X and Y, set Z to 1
	glm::vec3		velocity;						// For 2D use only X and Y, set Z to 0
	glm::mat4		modelMatrix;					// transform from model space [-0.5,0.5] to map space [0,MAP_SIZE]

	float			orientation;					// 0 radians is 3 o'clock, PI/2 radian is 12 o'clock
	int				gameObject_Direction;			// Facing: left = 0 and right = 1

	double							counter;		// use in state machine, to countdown the time in order to pause some movement

public:

	static GameObject*			GameObject_Instance_CREATE(int tag, glm::vec3 pos, glm::vec3 scale, glm::vec3 vel, float orient);
	static void					GameObject_Instance_DESTROY(GameObject &InstancePointer);

	/* For Draw f() */

	int							GetFlag();
	Mesh*						GetMesh();
	Texture*					GetTexture();
	glm::mat4					GetModelMatrix();
};
