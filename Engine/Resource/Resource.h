#pragma once
#include <string>

namespace squampernaut
{
	class Resource
	{
	public:

		virtual bool Create( std::string name, ... ) = 0;

	};
}