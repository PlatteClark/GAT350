#include "Actor.h"
#include "Factory.h"
#include "../Components/RenderComponent.h"

namespace squampernaut
{
		//We Clone'n
	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		m_transform = other.m_transform;
		m_scene = other.m_scene;

		for (auto& component : other.m_component)
		{
			auto clone = std::unique_ptr<Component>((Component*)component->clone().release());
			addComponent(std::move(clone));
		}
	}

		//I bet you guessed that this initializes actors. Good job.
	void Actor::Initialize()
	{
		for (auto& component : m_component)
		{
			component->Initialize();
		}

		for (auto& child : m_children)
		{
			child->Initialize();
		}
	}

		//This MIGHT update actors. Who knows?
	void Actor::Update()
	{
		if (!active){return;}

		if (lifespan != 0)
		{
			lifespan -= g_time.deltaTime;
			if (lifespan <= 0)
			{
				SetDestroy();
			}
		}
		

		for (auto& component : m_component){component->Update();}

		for (auto& child : m_children){child->Update();}

		if (m_parent){m_transform.Update(m_parent->m_transform.matrix);} 

		else 
		{ 
			m_transform.Update(); 
		}
		
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (!active){return;}
		for (auto& component : m_component)
		{
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
		}

		for (auto& child : m_children)
		{
			child->Update();
		}
	}

	void Actor::AddChild(std::unique_ptr<Actor> child)
	{
		child->m_parent = this;
		child->m_scene = m_scene;

		m_children.push_back(std::move(child));
	}

	void Actor::addComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_component.push_back(std::move(component));
	}

	bool Actor::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, tag);
		READ_DATA(value, name);
		READ_DATA(value, active);
		READ_DATA(value, lifespan);

		if (value.HasMember("transform")) m_transform.Read(value["transform"]);

		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& componentValue : value["components"].GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				if (component)
				{
					component->Read(componentValue);
					addComponent(std::move(component));
				}
			}
		}

		return true;
	}

}

