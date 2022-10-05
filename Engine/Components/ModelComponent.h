#pragma once

#include "RenderComponent.h"

namespace squampernaut
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelComponent)

		virtual void Update() override;

		virtual void Draw(Renderer& renderer) override;

	public:
		std::shared_ptr<Model> m_model;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	};
}