#pragma once
#include "../FrameWork/Component.h"
#include "../Math/Vector2.h"

namespace squampernaut
{
	class PhysicsComponent : public Component
	{
	public:
		CLASS_DECLARATION(PhysicsComponent)

		PhysicsComponent() = default;

		void Update() override;

		virtual void ApplyForce(const Vector2& force) { acceleration += force; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Vector2 velocity;
		Vector2 acceleration;

		float damping{ 1 };

	};
}