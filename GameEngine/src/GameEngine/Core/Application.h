#pragma once
#include "Core.h"

namespace Engine {
	class EN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* CreateApplication();
}

