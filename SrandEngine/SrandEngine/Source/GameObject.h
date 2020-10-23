#pragma once

#include "ECS.h"
#include "Component.h"

#include <vector>
#include <memory>

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args);

private:
	ComponentList compList;
	ComponentBitSet compBitSet;

	std::vector<std::unique_ptr<Component>> components;
};


template<typename T, typename... TArgs>
inline T& GameObject::AddComponent(TArgs&&... args) 
{

}