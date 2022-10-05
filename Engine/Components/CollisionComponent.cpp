#include "CollisionComponent.h"
#include "../Engine.h"

namespace squampernaut
{

    void CollisionComponent::Initialize()
    {
        auto component = m_owner->GetComponent<RBPhysicsComponent>();
        if (component)
        {
            // !! check data.size.x == 0 and data.size.y == 0) 
            if (data.size.x == 0 && data.size.y == 0)

            {
                // !! check render component from the owner 
                auto renderComponent = m_owner->GetComponent<RenderComponent>();
                if (renderComponent)
                {
                    data.size = Vector2{ renderComponent->GetSource().w, renderComponent->GetSource().h };
                }
            }
            data.size = data.size * scale_offset;

            if (component->m_body->GetType() == b2_staticBody)
            {
                g_physicsSystem.SetCollisionBoxStatic(component->m_body, data, m_owner);
            }
            else
            {
                g_physicsSystem.SetCollisionBox(component->m_body, data, m_owner);
            }
        }
    }

    void squampernaut::CollisionComponent::Update()
    {
    }

    void squampernaut::CollisionComponent::OnCollisionEnter(Actor* other)
    {
        if (m_enterFunction) m_enterFunction(other);
    }

    void squampernaut::CollisionComponent::OnCollisionExit(Actor* other)
    {
        if (m_exitFunction) m_exitFunction(other);
    }

    bool squampernaut::CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool squampernaut::CollisionComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);
        READ_DATA(value, scale_offset);

        return true;
    }

}