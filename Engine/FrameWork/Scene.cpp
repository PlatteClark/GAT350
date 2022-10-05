#include "Scene.h"
#include "Factory.h"
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

	void squampernaut::Scene::Draw(Renderer& renderer)
	{
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