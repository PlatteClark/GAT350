#pragma once 
#include "..\Math\Vector2.h" 
#include "../Resource/Resource.h"
#include "Renderer.h"
#include <string> 

struct SDL_Texture;

namespace squampernaut
{
	class Renderer;


	class Texture : public Resource
	{
		public:
			Texture() = default;
			~Texture();

			bool Create(std::string filename, ... ) override;

			bool Create(Renderer& renderer, const std::string& filename);

			void Bind() { glBindTexture(m_target, m_texture); }

			Vector2 GetSize() const;

			friend Renderer;

		private:
			GLuint m_texture { 0 };
			GLenum m_target = GL_TEXTURE_2D;
			GLuint m_unit = GL_TEXTURE0;

			//SDL_Texture* m_texture = nullptr; //2D stuff, no want no more
	};
}