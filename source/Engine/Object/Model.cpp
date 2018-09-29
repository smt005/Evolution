#include "Model.h"
#include "FileManager.h"
#include "Common/Help.h"

#define FILE_NAME_MODEL_DATA	"Models/Models.json"
#define FILE_NAME_SHAPE_FILE	"Models/Box1.obj"
#define FILE_NAME_TEXTURE_FILE	"Textures/BlackWhite.png"

Shape& Model::getShape()
{
	if (_shape) return *_shape;
	_shape = Shape::getByName(_name);
	return *_shape;
}

Mesh& Model::getMesh()
{
	if (_shape) return *_shape;
	_shape = Shape::getByName(_name);
	return *_shape;
}

Texture& Model::texture()
{
	if (_texture) return *_texture;
	_texture = Texture::getByName(_name);
	return *_texture;
}

const unsigned int& Model::textureId()
{
	if (_texture) return _texture->id();
	_texture = Texture::getByName(_name);
	return _texture->id();
}

bool Model::create(const string &newName)
{
	setName(newName);

	Json::Value dataModel = data(newName);
	if (dataModel.empty())
		return false;

	const string &nameShape = dataModel["shape"].empty() ? FILE_NAME_SHAPE_FILE : dataModel["shape"].asString();
	const string &nameTexture = dataModel["texture"].empty() ? FILE_NAME_TEXTURE_FILE : dataModel["texture"].asString();

	bool hasScalling = false;
	string suffixScale;

	if (!dataModel["scale"].empty())
	{
		if (dataModel["scale"].isArray())
		{
			int index = 0;

			auto& arrayScale = dataModel["scale"];


			for (auto it = arrayScale.begin(); it != arrayScale.end(); ++it)
			{
				float value = it->asFloat();
				_scale[index] = value;

				if (index >= 2) break;
				++index;

				string scaleString = std::to_string(value);
				if (suffixScale.empty())
				{
					suffixScale += scaleString;
				}
				else
				{
					suffixScale = suffixScale + "," + scaleString;
				}
			}

			hasScalling = true;
		}
		else
		{
			float value = dataModel["scale"].asFloat();

			if (value == 0.0f) {
				value = 1.0f;
			}

			_scale[0] = value;
			_scale[1] = value;
			_scale[2] = value;

			suffixScale = std::to_string(value);
			hasScalling = true;
		}
	}

	if (!hasScalling)
	{
		_shape = Shape::getByName(nameShape);
	}
	else
	{
		string nameWithSuffixScale = nameShape + "_[" + suffixScale + "]";

		if (Shape::hasByName(nameWithSuffixScale))
		{
			_shape = Shape::getByName(nameShape);
		}
		else
		{
			_shape = Shape::getByName(nameShape);

			_shape->setScale(_scale);
			_shape->setName(nameWithSuffixScale);
		}
	}
	
	_texture = Texture::getByName(nameTexture);

	return true;
}

// STATIC

Json::Value Model::_data;

Json::Value& Model::data(const string &name)
{
	if (_data.empty()) {
		help::loadJson(FILE_NAME_MODEL_DATA, _data);
	}

	return _data[name];
}

void Model::removeData()
{
	_data.clear();
}
