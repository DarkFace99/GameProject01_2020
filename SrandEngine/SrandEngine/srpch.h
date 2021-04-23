#pragma once

/* Stream and I/O */
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>

#include <bitset>
#include <memory>

/* STL Containers */
#include <vector>
#include <map>
#include <array>
#include <unordered_map>

/* Debugging Log */
#include "Log.h"

#define RATIO SCREEN_WIDTH / 480.0f

namespace Srand 
{
	template<typename T>
	T Abs(T num) 
	{
		return (num > 0) ? num : num * -1;
	}
}