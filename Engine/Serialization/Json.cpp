#include "Json.h"
#include "rapidjson/istreamwrapper.h"
#include "../Core/Logger.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include "../Math/Rect.h"
#include <fstream>

namespace squampernaut::json
{

    bool Load(const std::string& filename, rapidjson::Document& document)
    {

        std::ifstream stream(filename);
        if (stream.is_open() == false)
        {
            LOG("Error: couldn't open file %s", filename.c_str());
            return false;
        }

        rapidjson::IStreamWrapper istream(stream);
        document.ParseStream(istream);
        if (document.IsObject() == false)
        {
            LOG("json file cannot be read %s.", filename.c_str());
            return false;
        }

        return true;
    }

        //read Int
    bool Get(const rapidjson::Value& value, const std::string& name, int& data)
    {
        // check if 'name' member exists and is of type 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsNumber())
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetInt();
        return true;
    }

        //read Float
    bool Get(const rapidjson::Value& value, const std::string& name, float& data)
    {
            // check if 'name' member exists and is of type 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsNumber())
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

            // set data 
        data = value[name.c_str()].GetFloat();
        return true;
    }

        //read Bool
    bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
    {
            // check if 'name' member exists and is of type 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsBool())
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

            // set data 
        data = value[name.c_str()].GetBool();
        return true;
    }

        //read String
    bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        // check if 'name' member exists and is of type 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsString())
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetString();
        return true;
    }

        //read Vector2
    bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
            // check if 'name' member exists and is an array with 2 elements 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
            if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

            // create json array object 
        auto& array = value[name.c_str()];
            // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }

        //read Color
    bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

            // create json array object 
        auto& array = value[name.c_str()];
            // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }

        //get rect
    bool Get(const rapidjson::Value& value, const std::string& name, Rect& data)
    {

            // check if 'name' member exists and is an array with 2 elements 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

         // create json array object 
        auto& array = value[name.c_str()];

            // get array values 
        data.x = array[0].GetInt();
        data.y = array[1].GetInt();
        data.w = array[2].GetInt();
        data.h = array[3].GetInt();

        return true;

    }

    bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)

    {

        if (!value.HasMember(name.c_str()))
        {
            return false;
        }

        if (!value[name.c_str()].IsArray())
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsString())
            {
                LOG("error reading json data (not a string) %s", name.c_str());
                return false;
            }
            data.push_back(array[i].GetString());
        }

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
    {
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }

        if (!value[name.c_str()].IsArray())
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsInt())
            {
                LOG("error reading json data (not an int) %s", name.c_str());
                return false;
            }
            data.push_back(array[i].GetInt());
        }

        return true;
    }
    bool Get(const rapidjson::Value& value, const std::string& name, glm::vec2& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }
    bool Get(const rapidjson::Value& value, const std::string& name, glm::vec3& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }
    bool Get(const rapidjson::Value& value, const std::string& name, glm::vec4& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (!value.HasMember(name.c_str()))
        {
            return false;
        }
        if (!value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }
}