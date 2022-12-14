#include "Scene.h"
#include "../Engine.h"
#include <algorithm>
#include <iostream>

namespace squampernaut
{
	void Scene::Initialize()
	{
		for (auto& actor : m_actors) { actor->Initialize(); }
	}
	void Scene::Update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		// get camera / set renderer view/projection 
		auto camera = GetActorFromName("Camera");
		if (camera)
		{
			g_renderer.SetView(camera->GetComponent<CameraComponent>() -> GetView());
			g_renderer.SetProjection(camera->GetComponent<CameraComponent>() -> GetProjection());
		}

		// draw actors 
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void squampernaut::Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->SetDestroy(); }

		m_actors.clear();
	}

	bool Scene::Create(std::string name, ...)
	{
		// load scene 

		rapidjson::Document document;
		bool success = squampernaut::json::Load(name, document);
		if (!success)
		{
			LOG("error loading scene file %s.", name.c_str());
		}
		else
		{
			Read(document);
			Initialize();
		}

		return true;
	}

	bool squampernaut::Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
			//validate type
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}

			//read actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				actor->Read(actorValue);

				bool preFab = false;
				READ_DATA(actorValue, preFab);
				if (preFab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPreFab(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}

		return true;
	}
}