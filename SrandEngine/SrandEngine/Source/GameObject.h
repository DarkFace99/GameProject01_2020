#pragma once

#include "ECS.h"
#include "Component.h"
#include "Transform.h"

#include <vector>
#include <memory>

class GameObject
{
public:
	GameObject() 
	{
		this->AddComponent<Transform>(0, 0);
	}
	virtual ~GameObject() = default;

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args);

	template<typename T>
	inline T& GetComponent() const;

	template<typename T>
	inline bool HasComponent() const;

	inline bool Check_isActive() const;
	inline void Destroy();

	inline void Draw();
	inline void Update();

private:
	bool isActive;
	ComponentList compList;
	ComponentBitSet compBitSet;

	std::vector<std::unique_ptr<Component>> components;
};

inline void GameObject::Draw()
{
	for (auto& comp : components)
	{
		comp->Draw();
	}
}
inline void GameObject::Update()
{
	for (auto& comp : components)
	{
		comp->Update();
	}
}

template<typename T, typename... TArgs>
inline T& GameObject::AddComponent(TArgs&&... args) 
{
	T* comp(new T(std::forward<TArgs>(args)...));

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
inline bool GameObject::HasComponent() const
{
	return compBitSet[GetComponentID<T>()];
}

template<typename T>
inline T& GameObject::GetComponent() const
{
	auto ptr(compList[GetComponentID<T>()]);
	
	return *static_cast<T*>(ptr);
}

inline bool GameObject::Check_isActive() const 
{
	return isActive;
}

inline void GameObject::Destroy() 
{
	isActive = false;
}