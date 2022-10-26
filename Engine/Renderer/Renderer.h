#pragma once
#include <glad/glad.h> 
#include <SDL.h> 
#include "../Math/Vector2.h"
#include "Texture.h"
#include "../Math/Color.h"
#include "../Math/MathUtils.h"
#include "../Math/Matrix3x3.h"

struct SDL_Renderer;
struct SDL_Window;

namespace squampernaut
{
	struct Transform;
	class Texture;
	struct Rect;

	class Renderer
	{
	public:
		//constructer & destructer
		Renderer() = default;
		~Renderer() = default;

		void Initialize();
		void Shutdown();

		void CreateWindow(const char* name, int width, int height, bool fullscreen);
		void BeginFrame();
		void EndFrame();
		void SetClearColor(const Color color) { m_clearColor = color; }

		void DrawLine(const Vector2& v1, const Vector2& v2, const Color& color);
		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawPoint(float x, float y);
		void DrawPoint(const Vector2& v, const Color& color);

		int GetWidth()
		{
			return m_width;
		};
		int GetHeight()
		{
			return m_height;
		};

		void Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = Vector2{1,1}, const Vector2& registration = Vector2{0.5f,0.5f});
		void Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration = Vector2{ 0.5f,0.5f });
		void Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& registration = Vector2{ 0.5f, 0.5f }, bool flipH = false, bool flipV = false);

		const glm::mat4& GetView() { return m_view; }
		void SetView(const glm::mat4& view) { m_view = view; }

		const glm::mat4& GetProjection() { return m_projection; }
		void SetProjection(const glm::mat4& projection) { m_projection = projection; }

		friend class Text;
		friend class Texture;
	private:

		glm::mat4 m_view{ 1 };
		glm::mat4 m_projection{ 1 };

		SDL_GLContext m_context;

		int m_width;
		int m_height;

		Color m_clearColor{0, 0, 0, 255};

		SDL_Renderer* m_renderer{ nullptr };
		SDL_Window* m_window{ nullptr };
	};
}