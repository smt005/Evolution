
#pragma once

#include <string>
#include <vector>
#include "jsoncpp/include/json/json.h"
#include "glm/vec3.hpp"

namespace help
{
	bool loadJson(const std::string& fileName, Json::Value& value);
	bool intersection(glm::vec3 start1, glm::vec3 end1, glm::vec3 start2, glm::vec3 end2, glm::vec3 *out_intersection);
	float random_f(const float& min = 0.0f, const float& max = 1.0f, const int& accuracy = 1000);
	int random_i(const int& min = 0, const int& max = 1);

	float area—ircle(const float radius);
	float radius—ircle(const float volume);

	float volumeSphere(const float radius);
	float radiusSphere(const float value);

	template <class ObjectT>
	ObjectT& add(std::vector<ObjectT*>& vector)
	{
		ObjectT* newItem = new ObjectT();
		vector.push_back(newItem);
		return *newItem;
	}

	template <class ObjectT>
	void erase(std::vector<ObjectT*>& vector, const ObjectT item)
	{
		auto it = find(vector.begin(), vector.end(), item);

		if (it != vector.end())
		{
			vector.erase(it);
		}
	}

	template <class ObjectT>
	void erase(std::vector<ObjectT*>& vector, const std::string& name)
	{
		auto it = find_if(vector.begin(), vector.end(), [name](auto item)
		{
			if (!item)
				return false;

			if (item->name() == name)
				return true;
		});

		if (it != vector.end())
		{
			delete it->get();
			vector.erase(it);
		}
	}

	template <class ObjectT>
	void clear(std::vector<ObjectT*>& vector)
	{
		for (auto object : vector)
		{
			delete object;
		}

		vector.clear();
	}

	template <class ObjectT>
	ObjectT& find(std::vector<ObjectT*>& vector, const std::string& name)
	{
		auto it = find_if(vector.begin(), vector.end(), [name](auto item)
		{
			if (!item)
				return false;

			if (item->name() == name)
				return true;
		});

		if (it != vector.end())
		{
			return *(*it);
		}

		return ObjectT::defaultItem();
	}
}; // help