#include "Texture.h" 
#include "Renderer.h" 
#include "../Core/Logger.h"
#include <SDL.h> 
#include <SDL_image.h> 

namespace squampernaut
{
    Texture::~Texture()
    {
        if (m_texture != NULL)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    bool Texture::Create(std::string filename, ... )
    {
        va_list args;
        va_start(args, filename);

        Renderer& renderer = va_arg(args, Renderer);

        va_end(args);
        return Create(renderer, filename);
    }

    bool Texture::Create(Renderer& renderer, const std::string& filename)
    {
            // load surface 
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            LOG(SDL_GetError());
            return false;
        }
        
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        if (m_texture == nullptr)
        {
            LOG(SDL_GetError());
            SDL_FreeSurface(surface);

            return false;
        }

        SDL_FreeSurface(surface);
            return true;
    }

    squampernaut::Vector2 Texture::GetSize() const
    {
        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

            // !! return Vector2 of point.x, point.y 
        return { point.x, point.y };

    }
}