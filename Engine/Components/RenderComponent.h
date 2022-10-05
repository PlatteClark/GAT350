#pragma once
#include "../FrameWork/Component.h"
#include "../Math/Rect.h"
#include "../Math/Vector2.h"

namespace squampernaut
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& GetSource() { return source; }

		void SetFlipHorizontal(bool flip = true) { flipHorizontal = flip; }
		void SetFlipVertical(bool flip = true) { flipVertical = flip; }

		bool GetFlipHorizontal() { return flipHorizontal; }
		bool GetFlipVertical() { return flipVertical; }

	protected:

		Rect source;
		bool flipHorizontal = false;
		bool flipVertical = false;

		Vector2 registration = Vector2{ 0.5f, 0.5f };
	};
}