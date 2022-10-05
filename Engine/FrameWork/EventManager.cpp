#include "EventManager.h"

void squampernaut::EventManager::Initialize()
{
	//
}

void squampernaut::EventManager::Shutdown()
{
	//
}

void squampernaut::EventManager::Update()
{
	//
}

void squampernaut::EventManager::Subscribe(const std::string& name, Event::fuctionPtr function, GameObject* receiver)
{
	Observer observer;
	observer.receiver = receiver;
	observer.function = function;

	m_events[name].push_back(observer);
}

void squampernaut::EventManager::Unsubscribe(const std::string& name, GameObject* receiver)
{
	//
}

void squampernaut::EventManager::Notify(const Event& event)
{
	auto& observers = m_events[event.name];
	for (auto& observer : observers)
	{
		if (event.reciever == nullptr || event.reciever == observer.receiver)
		{
			observer.function(event);
		}
	}
}
