#pragma once

#include "jsoncpp/include/json/json.h"
#include "glm/mat4x4.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <string>

using namespace std;
using namespace glm;

class Model;
typedef std::shared_ptr<Model> ModelPtr;

class Object
{
protected:
	string _name;
	mat4x4 _matrix = mat4x4(1.0f);
	ModelPtr _model;

public:
	Object();
	Object(const string &name, const string &modelName, const vec3 &pos = vec3(0.0f), const Json::Value& data = Json::Value());
	virtual ~Object();

	void setName(const string& name) { _name = name; };

	const string& name() { return _name; };
	const mat4x4& getMatrix() { return _matrix; };
	const float* matrixFloat() { return value_ptr(_matrix); };
	void getDataJson(Json::Value& dataJson);

	void setMatrix(const mat4x4 &matrix) { _matrix = matrix; };
	void setMatrix(const float *matrix);

	Model& getModel();
	const float& getHeight();

	void set(const string &name, const string &modelName, const vec3 &pos = vec3(0.0f), const Json::Value& data = Json::Value());
	void setHeight(const float &height);
	void setVector(const glm::vec3 &vector);

public:
	virtual void setData(const Json::Value &data);
	virtual void action();

public:
	static Object* _default;

public:
	static Object& defaultItem();
	static void removeDefault();
};
