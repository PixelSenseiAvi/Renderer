#pragma once

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "GameEngine/CommonValues.h"

class ui
{
public:
	ui();

	void setupImgui(GLFWwindow* window);
	void drawImGuiOne();
	void drawImGuiTwo();
	void shutdownUI();
};

