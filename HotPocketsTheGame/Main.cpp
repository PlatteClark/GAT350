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
	auto scene = squampernaut::g_resources.Get<squampernaut::Scene>("Scenes/Texture.scn");

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, (float)squampernaut::g_renderer.GetWidth() / (float)squampernaut::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 2 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		squampernaut::Engine::Instance().Update();

		if (squampernaut::g_inputSystem.GetKeyState(squampernaut::key_escape) == squampernaut::InputSystem::KeyState::Pressed) quit = true;


		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{ 
			actor->m_transform.rotation.y += squampernaut::g_time.deltaTime * 90;
		}

		/*auto material = squampernaut::g_resources.Get<squampernaut::Material>("Materials/multi.mtrl");
		if (material)
		{
			material->uv_offset.x += squampernaut::g_time.deltaTime;
		}*/

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

upper to lower converter assignment. NOV 2nd
I have the base stuff in there, just need to flesh out.

*/