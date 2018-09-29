#pragma once

#include "jsoncpp/include/json/json.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "Common/DataClass.h"

#include <memory>
#include <vector>

class Object;
class Glider;
class Map;
typedef std::shared_ptr<Map> MapPtr;

class Map : public DataClass <Map>
{
public:
	std::vector<Object*> _objects;
	std::vector<Glider*> _gliders;

	Map() {};
	Map(const string &name);
	virtual ~Map();

	bool create(const string &name);

	void getDataJson(Json::Value& dataJson);
	void action();

	Object& addObjectToPos(const string& nameModel, const glm::vec3& pos = glm::vec3(0.0, 0.0, 0.0));
	Object& addObject(const string& nameModel, const glm::mat4x4& mat = glm::mat4x4(1.0));
};
