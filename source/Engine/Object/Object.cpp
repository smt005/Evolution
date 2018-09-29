
#include "Object.h"
#include "Model.h"
#include "Shape.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Object::Object()
{

}

Object::Object(const string &name, const string &modelName, const vec3 &pos, const Json::Value &data)
{
	set(name, modelName, pos, data);
}

Object::~Object()
{
}

void Object::getDataJson(Json::Value& dataJson)
{
	dataJson["name"] = name();
	dataJson["model"] = getModel().name();

	dataJson["pos"][0] =_matrix[3][0];
	dataJson["pos"][1] = _matrix[3][1];
	dataJson["pos"][2] = _matrix[3][2];
}

void Object::setMatrix(const float *matrix)
{
	_matrix[0][0] = matrix[0];
	_matrix[0][1] = matrix[1];
	_matrix[0][2] = matrix[2];
	_matrix[0][3] = matrix[3];

	_matrix[1][0] = matrix[4];
	_matrix[1][1] = matrix[5];
	_matrix[1][2] = matrix[6];
	_matrix[1][3] = matrix[7];

	_matrix[2][0] = matrix[8];
	_matrix[2][1] = matrix[9];
	_matrix[2][2] = matrix[10];
	_matrix[2][3] = matrix[11];

	_matrix[3][0] = matrix[12];
	_matrix[3][1] = matrix[13];
	_matrix[3][2] = matrix[14];
	_matrix[3][3] = matrix[15];
}

Model& Object::getModel()
{
	if (!_model) _model = Model::getByName("default");
	return *_model;
};

const float& Object::getHeight()
{
	return _matrix[3][2];
}

void Object::set(const string &name, const string &modelName, const vec3 &pos, const Json::Value &data)
{
	_name = name;
	_model = Model::getByName(modelName);

	if (length(pos) > 0.0f) _matrix = translate(_matrix, pos);
	if (!data.empty()) setData(data);
}

void Object::setHeight(const float &height)
{
	_matrix[3][2] = height;
}

void Object::setVector(const glm::vec3 &vector)
{

}

// Virtual

void Object::setData(const Json::Value &data)
{
}

void Object::action()
{

}


Object* Object::_default = nullptr;

Object& Object::defaultItem()
{
	if (!_default)
	{
		_default = new Object();
		_default->setName("DEFAULT_OBJECT");
	}

	return *_default;
}

void Object::removeDefault()
{
	delete _default;
	_default = nullptr;
}
