#include "Model.h"
#include "../Math/Transform.h"
#include "../Math/MathUtils.h"
#include "../Core/File.h"
#include "../Core/Logger.h"
#include <sstream>
#include <iostream>



namespace squampernaut
{
    Model::Model(const std::string& filename)
    {
        Load(filename);
        m_radius = CalculateRadius();
    }
    bool Model::Create( std::string filename, ... )
    {
        if (!Load(filename))
        {
            LOG("Error: Could not read model %s", filename.c_str());
            return false;
        }
        return true;
    }
    void Model::Draw(Renderer& renderer, Vector2& position,float angle, const Vector2& scale)
    {

            //draw model
        for (int i = 0; i < m_points.size() - 1; i++)
        {
            squampernaut::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
            squampernaut::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

            renderer.DrawLine(p1, p2, m_color);
        }
    }
    void Model::Draw(Renderer& renderer, const Transform& transform)
    {
        /*
        Matrix3x3 mx = transform.matrix;
         //draw model
        for (int i = 0; i < m_points.size() - 1; i++)
        {
            squampernaut::Vector2 p1 = mx * m_points[i];
            squampernaut::Vector2 p2 = mx * m_points[i + 1];

            renderer.DrawLine(p1, p2, m_color);
        }
        */
    }

    bool Model::Load(const std::string& filename)
    {
        std::string buffer;

        if (!ReadFile(filename, buffer))
        {
            LOG("Error: Could not read file %s", filename.c_str());
            return false;
        }

            //read color
        std::istringstream stream(buffer);
        stream >> m_color;

        std::string line;
        std::getline(stream, line);

            //get number of points
        size_t numPoints = std::stoi(line);

            //read model points
        for (rsize_t i = 0; i < numPoints; i++)
        {
            Vector2 point;

            stream >> point;
            m_points.push_back(point);
        }

        return true;
    }
    float Model::CalculateRadius()
    {
        float radius = 0;

            //find the largest length (radius)
        for (auto& point : m_points)
        {
            if (point.length() > radius)
            {
                radius = point.length();
            }
        }

        return radius;
    }
}