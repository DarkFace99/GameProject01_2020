#include "GameObject.h"

static Mesh		    meshArray[MAX_MESH];							// Store all unique shape/mesh in your game
static int			numMesh;
static Texture		texArray[MAX_TEXTURE];							// Corresponding texture of the mesh
static int			numTex;
static GameObject	gameObjectInstance_Array[MAX_INSTANCE_GAMEOBJECTS];			// Store all game object instance
static int			numGameObj;



GameObject* GameObject::gameObject_Instance_CREATE(int tag, glm::vec3 pos, glm::vec3 scale, glm::vec3 vel, float orient)
{
	for (int i = 0; i < MAX_INSTANCE_GAMEOBJECTS; i++) {
		GameObject* InstancePointer = gameObjectInstance_Array + i;
		if (InstancePointer->flag == FLAG_INACTIVE_GAMEOBJECT) {

			InstancePointer->mesh = meshArray + tag;
			InstancePointer->texture = texArray + tag;
			InstancePointer->c_tag = tag;
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
void GameObject::gameObject_Instance_DESTROY(GameObject& InstancePointer) 
{
	// Not deleting the object, just check if the component is Active or Inactive
	if (InstancePointer.flag == FLAG_INACTIVE_GAMEOBJECT)
		return;

	numGameObj--;
	InstancePointer.flag = FLAG_INACTIVE_GAMEOBJECT;
}
