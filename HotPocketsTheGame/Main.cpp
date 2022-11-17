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

	squampernaut::g_gui.Initialize(squampernaut::g_renderer);

	// load scene 
	auto scene = squampernaut::g_resources.Get<squampernaut::Scene>("Scenes/Cube.scn");

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, (float)squampernaut::g_renderer.GetWidth() / (float)squampernaut::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 2 };
	float speed = 3;

	glm::vec3 rot = { 0, 0, 0 };
	float ri = 1;
	bool quit = false;
	while (!quit)
	{
		squampernaut::Engine::Instance().Update();
		squampernaut::g_gui.BeginFrame(squampernaut::g_renderer);

		if (squampernaut::g_inputSystem.GetKeyState(squampernaut::key_escape) == squampernaut::InputSystem::KeyState::Pressed) quit = true;


		auto actor = scene->GetActorFromName("Model");
		if (actor)
		{ 
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}
		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave 
			//actor->m_transform.position = pos;
			//actor->m_transform.position.y = std::sin(squampernaut::g_time.time);
		}

		auto program = squampernaut::g_resources.Get<squampernaut::Program>("Shaders/FX/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();
		squampernaut::g_renderer.BeginFrame();

		scene->PreRender(squampernaut::g_renderer);

		scene->Render(squampernaut::g_renderer);
		squampernaut::g_gui.Draw();

		squampernaut::g_renderer.EndFrame();
		squampernaut::g_gui.EndFrame();
	}

	scene->RemoveAll();
	squampernaut::Engine::Instance().Shutdown();
	return 0;
}

/* TODO

*/