#pragma once 
#include "..\Math\Vector2.h" 
#include "../Resource/Resource.h"
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

			Vector2 GetSize() const;

			friend Renderer;

		private:
			SDL_Texture* m_texture = nullptr;
	};
}