#pragma once

#include "jsoncpp/include/json/json.h"
#include "Common/DataClass.h"
#include "Object/Shape.h"
#include "Object/Texture.h"

#include <string>

class Model;
typedef std::shared_ptr<Model> ModelPtr;

class Model : public DataClass <Model>
{
private:
	ShapePtr _shape;
	TexturePtr _texture;
	float _scale[3];

public:
	Shape& getShape();
	Mesh& getMesh();
	Texture& texture();
	const unsigned int& textureId();

	bool create(const std::string &name);

private:
	static Json::Value _data;

public:
	static Json::Value& data(const std::string &name);
	static void removeData();
};
