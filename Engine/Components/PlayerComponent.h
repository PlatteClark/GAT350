#pragma once
#include "../FrameWork/Component.h"
#include "../Physics/Collision.h"
#include "../Components/CharacterComponent.h"

namespace squampernaut
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		CLASS_DECLARATION(PlayerComponent)

		PlayerComponent() = default;

		void Initialize() override;
		void Update() override;

		virtual void OnNotify(const Event& event) override;
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float jump{ 3000 };
		int m_groundCount = 0;


	};
}