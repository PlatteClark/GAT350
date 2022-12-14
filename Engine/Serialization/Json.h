#pragma once
#include "rapidjson/document.h"
#include "../Math/MathUtils.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

#define READ_DATA(value, data) squampernaut::json::Get(value, #data, data)

namespace squampernaut
{
	struct Vector2;
	struct Color;
	struct Rect;
}

namespace squampernaut::json
{
	bool Load(const std::string& filename, rapidjson::Document& document);

	bool Get(const rapidjson::Value& value, const std::string& name, int& data);
	bool Get(const rapidjson::Value& value, const std::string& name, float& data);
	bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
	bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
	bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
	bool Get(const rapidjson::Value& value, const std::string& name, Rect& data);
	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);

	bool Get(const rapidjson::Value& value, const std::string& name, glm::vec2& data);
	bool Get(const rapidjson::Value& value, const std::string& name, glm::vec3& data);
	bool Get(const rapidjson::Value& value, const std::string& name, glm::vec4& data);

}