#pragma once
#include <string>
#include <variant>
#include <functional>

namespace squampernaut
{
	class GameObject;

	class Event
	{
	public:
		using fuctionPtr = std::function<void(const Event&)>;


	public:
		std::string name;
		GameObject* reciever{ nullptr };
		std::variant<int, bool, float, std::string> data;

	};
	class INotify
	{
	public:
		virtual void OnNotify(const Event& event) = 0;
	};
}