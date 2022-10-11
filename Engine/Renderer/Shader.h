#pragma once
#include "../Resource/Resource.h"
#include "Renderer.h"

namespace squampernaut
{
	class Shader : public Resource
	{
	public:
		~Shader();

		// Inherited via Resource
		virtual bool Create(std::string name, ...) override;

	public:
		GLuint m_shader = 0;
	};
}