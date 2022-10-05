#include "SpriteComponent.h"
#include "../Renderer/Renderer.h"
#include "../FrameWork/Actor.h"
#include "../Renderer/Texture.h"
#include "../Engine.h"

namespace squampernaut
{
	void SpriteComponent::Update()
	{
	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(m_texture, GetSource(), m_owner->m_transform, registration, flipHorizontal, flipVertical);
	}

	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		std::string texture_name;
		READ_DATA(value, texture_name);

		m_texture = g_resources.Get<Texture>(texture_name, g_renderer);

		if (!READ_DATA(value, source))
		{
			source.x = 0;
			source.y = 0;
			source.w = (int)m_texture->GetSize().x;
			source.w = (int)m_texture->GetSize().y;

		}

		return true;
	}
}
