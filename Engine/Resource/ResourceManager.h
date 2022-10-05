#pragma once
#include "Resource.h"
#include <map>
#include <string>
#include <memory>


namespace squampernaut
{
	class ResourceManager
	{
		
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Initialize();
		void Shutdown();

		template <typename T, typename ... Targs>
		std::shared_ptr<T> Get(std::string name, Targs ... args);

	private:
		
			//map< key, data >
		std::map < std::string, std::shared_ptr<Resource> > m_resources;

	};
	template<typename T, typename ... Targs>
	inline std::shared_ptr<T> ResourceManager::Get(std::string name, Targs ... args)
	{
		if (m_resources.find(name) != m_resources.end())
		{
				//found
			return std::dynamic_pointer_cast<T>(m_resources[name]);
		}
		else
		{
				//no finded
			std::shared_ptr<T> resource = std::make_shared<T>();
			resource->Create(name, args ... );
			m_resources[name] = resource;

			return resource;
		}
	}
}