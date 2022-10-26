#include "Engine.h" 
#include <iostream> 


int main(int argc, char** argv)
{
	LOG("Application Started...");
	squampernaut::InitializeMemory();

	squampernaut::SetFilePath("../Assets");

	squampernaut::Engine::Instance().Initialize();
	squampernaut::Engine::Instance().Register();

	LOG("Engine Initialized...");

	squampernaut::g_renderer.CreateWindow("Game", 800, 600, false);

	LOG("Window Created...");

	// load scene 
	auto scene = squampernaut::g_resources.Get<squampernaut::Scene>("Scenes/basic.scn");

	// create material 
	std::shared_ptr<squampernaut::Material> material = squampernaut::g_resources.Get<squampernaut::Material>("Materials/ogre.mtrl");
	material->Bind();

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, (float)squampernaut::g_renderer.GetWidth() / (float)squampernaut::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 2 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		squampernaut::Engine::Instance().Update();

		if (squampernaut::g_inputSystem.GetKeyState(squampernaut::key_escape) == squampernaut::InputSystem::KeyState::Pressed) quit = true;

		scene->Update();
		squampernaut::g_renderer.BeginFrame();
		scene->Draw(squampernaut::g_renderer);

		squampernaut::g_renderer.EndFrame();
	}

	scene->RemoveAll();
	squampernaut::Engine::Instance().Shutdown();
	return 0;
}

/* TODO
create basic_lit.scn.
change auto scene = squampernaut::g_resources.get(scenestuff) to lit.scn
get the light scene stuff from teams and put it after the scene stuff.

*/