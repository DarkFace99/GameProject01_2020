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

	template<typename T>
	inline T& GetComponent() const;

private:
	ComponentList compList;
	ComponentBitSet compBitSet;

	std::vector<std::unique_ptr<Component>> components;
};


template<typename T, typename... TArgs>
inline T& GameObject::AddComponent(TArgs&&... args) 
{
	T* comp(new T(std::forward<TArgs>(args...)));

	std::unique_ptr<Component> unique_ptr { comp };								// Convert comp as a unique pointer so we can store
	components.emplace_back(std::move(unique_ptr));

	if (comp->Init())															// If is created properly 
	{
		//std::cout << "Component Initiated: SUCCEED" << std::endl;

		compList[GetComponentID<T>()] = comp;
		compBitSet[GetComponentID<T>()] = true;

		comp->gameObject = this;												// Attached the component to the gameObject

		return *comp;
	}
	else 
	{
		//std::cout << "Component Initiated: FAILED" << std::endl;
		return *static_cast<T*>(nullptr);
	}
}

template<typename T>
inline T& GameObject::GetComponent() const
{
	auto ptr(compList[GetComponentID<T>()]);

	return *static_cast<T*>(ptr);
}