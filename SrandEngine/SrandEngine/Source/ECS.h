#pragma once

#include <iostream>
#include <array>
#include <bitset>

class GameObject;
class Component;

constexpr std::size_t MAX_GAMEOBJECT = 2000;    // just a normal define with make it unsigned and const
constexpr std::size_t MAX_GAMECOMPONENT = 30;   // just a normal define with make it unsigned and const

using GameObjectList = std::bitset<MAX_GAMEOBJECT>;
using ComponentList = std::bitset<MAX_GAMECOMPONENT>;
using ComponentTypeID = std::size_t;

inline ComponentTypeID GetComponentID()
{
    static ComponentTypeID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentTypeID GetComponentTypeID() noexcept
{
    static_assert(std::is_base_of<GameComponent, T>::value, "Not Based on GameComponent!");
    static const ComponentTypeID typeID = GetComponentID(); // To get the component ID as a const
    return typeID;
}