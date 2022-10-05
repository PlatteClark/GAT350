#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <memory>


namespace squampernaut
{
	class Scene;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}
		~Actor() = default;

		CLASS_DECLARATION(Actor)

		void Initialize() override;

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		void addComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other){}
		float GetRadius() { return 0; }// m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y);

		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }

		void SetDestroy() { m_destroy = true; }
		bool IsDestroyed() { return m_destroy; }
		void SetActive(bool active) { this->active = active; }
		bool IsActive() { return active; }

		Scene* GetScene() { return m_scene; }


		friend class Scene;
		Transform m_transform;

	protected:

		float lifespan = 0;

		std::string name;
		std::string tag;

		bool active = true;
		bool m_destroy = false;

		Scene* m_scene;	
		Actor* m_parent{ nullptr };

		std::vector<std::unique_ptr<Component>> m_component;
		std::vector<std::unique_ptr<Actor>> m_children;
	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& comp : m_component)
		{
			T* result = dynamic_cast<T*> (comp.get());
			if (result) return result;
		}

		return nullptr;
	}

}