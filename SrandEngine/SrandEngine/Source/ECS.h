#pragma once

#include <iostream>
#include <array>
#include <bitset>

class GameObject;
class Component;

constexpr std::size_t MAX_GAMEOBJECTS = 2000;                                                   // Just a normal define with make it unsigned and const
constexpr std::size_t MAX_COMPONENTS = 30;                                                      // Just a normal define with make it unsigned and const

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;                                            // Array of Booleans
using ComponentList = std::array<Component* , MAX_COMPONENTS>;

using ComponentID = std::size_t; // store the size of the array

inline ComponentID GetComponentUniqueID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentID GetComponentID() noexcept
{
    static_assert(std::is_base_of<GameComponent, T>::value, "Not Based on GameComponent!");     // To check if the class that is using the function is a base class of GameComponent or not
    static const ComponentID ID = GetComponentUniqueID();                                       // To get the component ID as a const
    return ID;
}