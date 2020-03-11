#include "GameEngine.h"
#include "TransmittanceEffects.h"

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new TransmittanceEffects());
	}
	~Sandbox()
	{
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}