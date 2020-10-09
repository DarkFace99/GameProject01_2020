#pragma once

#include "ECS.h"
#include "Component.h"

#include <vector>
#include <memory>

class GameObject
{
private:
    GameObjectList gameObjectList;
    ComponentList componentList;

    std::vector<std::unique_ptr<Component>> components;
public:
    GameObject();
    virtual ~GameObject();

    template<typename T, typename... T_Argument>
    inline T& AddComponent(T_Argument&&... arguments)
    {
        T* compo(new T(std::forward<T_Argument>(arguments...)));

        std::unique_ptr<Component> uptr{ compo };
        components.emplace_back(std::move(uptr));
        compo->gameObject = this;

        if (compo->Init() == true)
        {
            componentList[GetComponentTypeID<T>()] = compo;
            GameObjectList[GetComponentTypeID<T>()] = true;
            compo->gameObject = this;
            return *compo;
        }
        return *static_cast<T*>(nullptr);
    }

    template<typename T>
    inline T& GetComponent() const
    {
        auto ptr(ComponentList[GetComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};
