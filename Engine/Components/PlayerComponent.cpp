#include "PlayerComponent.h"
#include "../Engine.h"
#include <iostream>
#include "../Components/PhysicsComponent.h"

void squampernaut::PlayerComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void squampernaut::PlayerComponent::Update()
{

    Vector2 direction = Vector2::zero;

    // set camera 
    auto camera = m_owner->GetScene()->GetActorFromName("Camera");
    if (camera)
    {
        camera->m_transform.position = math::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
    }

    if (squampernaut::g_inputSystem.GetKeyState(key_left))
    {
        direction = Vector2::left;
    }

    if (squampernaut::g_inputSystem.GetKeyState(key_right))
    {
        direction = Vector2::right;
    }

    Vector2 velocity;
    auto component = m_owner->GetComponent<PhysicsComponent>();
    if (component)
    {
        // if in the air (m_groundCount == 0) then reduce force 
        float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

        component->ApplyForce(direction * speed * multiplier);
        velocity = component->velocity;
    }

        //jump
    if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
    {
        auto component = m_owner->GetComponent<PhysicsComponent>();
        if (component)
        {
            component->ApplyForce(Vector2::up * 200);
        }
    }
    auto animComponent = m_owner->GetComponent<SpriteAnimationComponent>();
    if (animComponent)
    {
        if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
        if (std::fabs(velocity.x) > 0)
        {
            animComponent->SetSequence("run");
        }
        else
        {
            animComponent->SetSequence("idle");
        }
    }
}

bool squampernaut::PlayerComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool squampernaut::PlayerComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);
    READ_DATA(value, jump);

    return true;
}
void squampernaut::PlayerComponent::OnNotify(const Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            //die
        }
    }
    //if (event.name == "whatever") blah blah add more events if you want
}
    //bing bong when things go bonk
void squampernaut::PlayerComponent::OnCollisionEnter(Actor* other)
{

    if (other->GetTag() == "Ground")
    {
        m_groundCount++;
    }
    if (other->GetName() == "tile01")
    {
        Event event;
        event.name = "EVENT_ADD_POINTS";
        event.data = 100;

        g_eventManager.Notify(event);
    }
    if (other->GetTag() == "Enemy")
    {
        Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.reciever = other;

        g_eventManager.Notify(event);
    }
}

void squampernaut::PlayerComponent::OnCollisionExit(Actor* other)
{
    if (other->GetTag() == "Ground")
    {
        m_groundCount--;
    }
}
