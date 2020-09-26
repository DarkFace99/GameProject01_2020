#include "GameObject.h"


Mesh		    meshArray[MAX_MESH];							// Store all unique shape/mesh in your game
int				numMesh;
Texture			texArray[MAX_TEXTURE];							// Corresponding texture of the mesh
int				numTex;
GameObject		gameObjectInstance_Array[MAX_INSTANCE_GAMEOBJECTS];			// Store all game object instance
int				numGameObj;



GameObject* GameObject::GameObject_Instance_CREATE(int tag, glm::vec3 pos, glm::vec3 scale, glm::vec3 vel, float orient, int control)
{
	for (int i = 0; i < MAX_INSTANCE_GAMEOBJECTS; i++) {
		GameObject* InstancePointer = gameObjectInstance_Array + i;
		if (InstancePointer->flag == FLAG_INACTIVE_GAMEOBJECT) {

			InstancePointer->mesh = meshArray + tag;
			InstancePointer->texture = texArray + tag;
			InstancePointer->g_tag = tag;
			InstancePointer->controlling = control;
			InstancePointer->flag = FLAG_ACTIVE_GAMEOBJECT;
			InstancePointer->position = pos;
			InstancePointer->velocity = vel;
			InstancePointer->scale = scale;
			InstancePointer->orientation = orient;
			InstancePointer->modelMatrix = glm::mat4(1.0f);

			numGameObj++;
			return InstancePointer;
		}
	}

	// Cannot find empty slot => return 0
	return NULL;
}
void GameObject::GameObject_Instance_DESTROY(GameObject& InstancePointer) 
{
	// Not deleting the object, just check if the component is Active or Inactive
	if (InstancePointer.flag == FLAG_INACTIVE_GAMEOBJECT)
		return;

	numGameObj--;
	InstancePointer.flag = FLAG_INACTIVE_GAMEOBJECT;
}

/* For Draw f() */
int			GameObject::GetFlag()		{ return flag; }
Mesh*		GameObject::GetMesh()		{ return mesh; }
Texture*	GameObject::GetTexture()	{ return texture; }
int			GameObject::GetTag()		{ return g_tag; }
int			GameObject::GetControl()	{ return controlling; }

glm::mat4	GameObject::GetModelMatrix() { 
	
	glm::mat4 resultMat = glm::mat4(1.0f);
	resultMat = glm::translate(resultMat, position);
	resultMat = glm::scale(resultMat, scale);
	resultMat = glm::rotate(resultMat, orientation * 3.14f/180.0f, glm::vec3(0,0,1));
	return resultMat;
}

glm::vec3 GameObject::GetPosition()
{
	return position;
}
glm::vec3 GameObject::GetScale() 
{
	return scale;
}