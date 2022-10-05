#pragma once
#include "Renderer.h"
#include <vector>
#include <string>
#include "../Resource/Resource.h"



namespace squampernaut
{
    class Model : public Resource
    {
    public:
        Model() = default;
        Model(const std::vector<squampernaut::Vector2>& points, const squampernaut::Color& color) : m_points{ points }, m_color{ color } //Set private vars with constructor
        {
        }
        Model(const std::string& filename);

        bool Create( std::string filename, ... ) override;

        void Draw(Renderer& renderer, Vector2& position, float angle, const Vector2& scale = Vector2{1,1});
        void Draw(Renderer& renderer, const Transform& transform);

        bool Load(const std::string& fileName);

        float CalculateRadius();
        float GetRadius() { return m_radius; }

    private:
        squampernaut::Color m_color{ 0, 0, 0, 0};
        std::vector<squampernaut::Vector2> m_points;

        float m_radius = 0;
    };
}