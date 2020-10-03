#include "GameObject.h"

Mesh		    meshArray[MAX_MESH];							// Store all unique shape/mesh in your game
int				numMesh;
Texture			texArray[MAX_TEXTURE];							// Corresponding texture of the mesh
int				numTex;
GameObject		gameObjectInstance_Array[MAX_INSTANCE_GAMEOBJECTS];			// Store all game object instance
int				numGameObj;



GameObject* GameObject::GameObject_Instance_CREATE(int tag, glm::vec3 pos, glm::vec3 scale, glm::vec3 vel, float orient, bool setAnim, int numFrame)
{
	for (int i = 0; i < MAX_INSTANCE_GAMEOBJECTS; i++) {
		GameObject* InstancePointer = gameObjectInstance_Array + i;
		if (InstancePointer->flag == FLAG_INACTIVE_GAMEOBJECT) {

			InstancePointer->mesh = meshArray + tag;
			InstancePointer->texture = texArray + tag;
			InstancePointer->tag = tag;
			InstancePointer->flag = FLAG_ACTIVE_GAMEOBJECT;
			InstancePointer->position = pos;
			InstancePointer->velocity = vel;
			InstancePointer->scale = scale;
			InstancePointer->orientation = orient;
			InstancePointer->modelMatrix = glm::mat4(1.0f);
			InstancePointer->animActivate = setAnim;
			InstancePointer->numFrame = numFrame;
			InstancePointer->offsetX = 0.0f;
			//InstancePointer->offsetY = 0.0f;

			
			InstancePointer->position.z = InstancePointer->tag;		// assign layer according to game object tag
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
int			GameObject::GetFlag() { return flag; }
Mesh*		GameObject::GetMesh() { return mesh; }
Texture*	GameObject::GetTexture() { return texture; }
glm::mat4	GameObject::GetModelMatrix() { 
	
	glm::mat4 resultMat = glm::mat4(1.0f);
	resultMat = glm::translate(resultMat, position);
	resultMat = glm::scale(resultMat, scale);
	resultMat = glm::rotate(resultMat, orientation * 3.14f/180.0f, glm::vec3(0,0,1));
	return resultMat;
}

bool GameObject::GetAnimStatus()
{
	return animActivate;
}
void		GameObject::IncrementOffsetX()
{
	GameObject::offsetX += 1.0f / (float)GameObject::numFrame;
	if (GameObject::offsetX > ((float)GameObject::numFrame - 0.9f) / (float)GameObject::numFrame) 
	{
		GameObject::offsetX = 0.0f;
	}
}
//void		GameObject::SetOffsetY(float offsetY) 
//{
//	GameObject::offsetY = offsetY;
//}
float		GameObject::GetOffsetX()
{
	return offsetX;
}
//float		GameObject::GetOffsetY()
//{
//	return offsetY;
//}

		