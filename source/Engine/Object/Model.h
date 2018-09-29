#pragma once

#include "jsoncpp/include/json/json.h"
#include "Common/DataClass.h"
#include "Object/Shape.h"

#include <string>
using namespace std;

class Model;
typedef std::shared_ptr<Model> ModelPtr;

class Model : public DataClass <Model>
{
private:
	ShapePtr _shape;
	float _scale[3];

public:
	Shape& getShape();
	Mesh& getMesh();

	bool create(const string &name);

private:
	static Json::Value _data;

public:
	static Json::Value& data(const string &name);
	static void removeData();
};
