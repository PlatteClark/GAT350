#pragma once
#include <list>
#include <memory>
#include "Actor.h"
#include "../Resource/Resource.h"

namespace squampernaut
{
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable, public Resource
	{

	public:
		Scene() = default;
		~Scene() = default;
		Scene(Game* game) : m_game{ game } {};
		Scene(const Scene& other) {};

		CLASS_DECLARATION(Scene)

		void Initialize() override;

		virtual bool Create(std::string name, ...) override;

		void Update() override;

		void PreRender(Renderer& renderer);
		void Render(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		Game* GetGame() { return m_game; }

		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsFromTag(const std::string& tag);

	private:
		Game* m_game;
		std::list<std::unique_ptr<Actor>> m_actors;



	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result)
			{
				return result;
			}
		}
		return nullptr;
	};

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		//  !! for loop (range based) through m_actors 
		for (auto& actor : m_actors)
		{
			//  !! compare name to actor GetName()
			if (actor->GetName() == name)
			{
				//  !! get() actor pointer
				return dynamic_cast<T*>(actor.get());
			}
		}

		return nullptr;
	};

	template<typename T>
	inline std::vector<T*> Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		//  !! for loop (range based) through m_actors 
		for (auto& iter : m_actors)
		{
			//  !! compare name to actor GetName()
			if (iter == Actor::GetName())
			{
				//  !! get() actor pointer
				T* tagActor = dynamic_cast<T*>(iter.get());
				if (tagActor) { result.push_back(tagActor); }
				//  !! push back tagActor to result vector 
			}
		}

		return result;
	};
}