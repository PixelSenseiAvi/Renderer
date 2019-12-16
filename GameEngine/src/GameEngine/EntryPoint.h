#pragma once
#include "Log.h"

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	CORE_WARN("Initilize Log");
	int a = 5;
	CL_INFO("Test, Var = {0}", a);
	auto app = Engine::CreateApplication();
	app->run();
	delete app;
}
#endif