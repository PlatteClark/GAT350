#include "Engine.h" 
#include <iostream> 

int main()
{
	squampernaut::InitializeMemory();

	squampernaut::Engine::Instance().Initialize();
	squampernaut::Engine::Instance().Register();

	squampernaut::g_renderer.CreateWindow("Game", 800, 600);

	bool quit = false;
	while (!quit)
	{
		squampernaut::Engine::Instance().Update();

		if (squampernaut::g_inputSystem.GetKeyState(squampernaut::key_escape) == squampernaut::InputSystem::KeyState::Pressed) quit = true;

		squampernaut::g_renderer.BeginFrame();
		squampernaut::g_renderer.EndFrame();
	}

	squampernaut::Engine::Instance().Shutdown();
}