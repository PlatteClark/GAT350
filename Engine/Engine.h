#pragma once

#include "Serialization/Json.h"

#include "Physics/PhysicsSystem.h"
#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Vector2.h"

#include "FrameWork/Scene.h"
#include "FrameWork/Game.h"
#include "FrameWork/Singleton.h"
#include "FrameWork/Factory.h"
#include "FrameWork/EventManager.h"

#include "Components/CameraComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteAnimationComponent.h"
#include "Components/TilemapComponent.h"
#include "Components/CharacterComponent.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Material.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Shader.h"
#include "Renderer/Program.h"
#include "glm/glm.hpp"

#include<memory>
#include <vector>
#include <list>
#include <variant>


namespace squampernaut
{
	extern InputSystem g_inputSystem;
	extern PhysicsSystem g_physicsSystem;
	extern Renderer g_renderer;
	extern Time g_time;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resources;
	extern EventManager g_eventManager;

	class Engine : public Singleton<Engine>
	{
	public:
		void Initialize();
		void Shutdown();

		void Update();

		void Register();
	};
	
}