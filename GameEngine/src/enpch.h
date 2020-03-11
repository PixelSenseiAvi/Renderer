#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <utility>
#include <functional>

#include <string>
#include <vector>
#include <sstream>

#ifdef EN_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

namespace constants
{
	const float GLOBAL_toRadians = 3.14159265f / 180.0f;
	
	//default shaders
	// Vertex Shader
	static const char* vShader = "Shaders/shader.vert";
	// Fragment Shader
	static const char* fShader = "Shaders/shader.frag";
}

