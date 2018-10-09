
#include "glew/include/GL/glew.h"
#include <functional>

#include "Common/Help.h"
#include "FileManager.h"

#include "Triangle.h"

TexturePtr textureStatic;

Triangle::~Triangle()
{
	if (_points) {
		delete[] _points;
	}
}

// Template

Json::Value templateJsonMake;

void Triangle::Template::makeData()
{
	static Point pointsStatic[] = { -0.425f, -0.9f, 0.0f,
									0.575f, 0.0f, 0.0f,
									-0.425f, 0.9f, 0.0f };

	static TexCoord texCoordStatic[] = { 1.715f, 0.0f,
										0.0f, 0.0f,
										0.0f, 1.715f };

	for (unsigned int i = 0; i < 3; ++i) {
		points[i] = pointsStatic[i] * scale;
	}

	if (dist > 0.0f) {
		glm::vec3 vecNormalize = glm::normalize(vector);
		glm::vec3 posParent(0.0f);

		if (parent) {
			posParent = parent->pos;
		}

		pos = vecNormalize * dist;
		pos += posParent;

		for (unsigned int i = 0; i < 3; ++i) {
			points[i] += pos;
		}
	}

	memcpy(texCoord, texCoordStatic, sizeof(TexCoord) * 3);

	int intPtr = reinterpret_cast<int>(this);
	const std::string stringPtr = std::to_string(intPtr);

	for (int i = 0; i < 3; ++i)
	{
		templateJsonMake[stringPtr]["points"].append(points[i].data[0]);
		templateJsonMake[stringPtr]["points"].append(points[i].data[1]);
		templateJsonMake[stringPtr]["points"].append(points[i].data[2]);
	}

	for (const auto& item : childs) {
		item->makeData();
	}
}

void Triangle::Template::make()
{
	makeData();
}

bool Triangle::initVBO()
{
	glDeleteBuffers(2, _buffer);
	glGenBuffers(2, _buffer);

	if (_count == 0 || !_points) {
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, _count * 3 * sizeof(GLfloat), _points, GL_STATIC_DRAW);

	if (_texCoord) {
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, _count * 2 * sizeof(GLfloat), _texCoord, GL_STATIC_DRAW);
	}

	_hasVBO = true;
	return _hasVBO;
}

// STATIC

void Triangle::makeTriangle(Triangle& triangle, const float& scale)
{
	static unsigned short int typeStatic = Triangle::TRIANGLES;
	static unsigned int countStatic = 3;
	static Point pointsStatic[] = { -0.425f, -0.9f, 0.0f,
									0.575f, 0.0f, 0.0f,
									-0.425f, 0.9f, 0.0f };

	static TexCoord texCoordStatic[] = { 1.715f, 0.0f,
										0.0f, 0.0f,
										0.0f, 1.715f };

	triangle._type = typeStatic;
	triangle._count = countStatic;
	triangle._points = new Point[countStatic];

	for (unsigned int i = 0; i < countStatic; ++i) {
		triangle._points[i] = pointsStatic[i] * scale;
	}

	triangle._texCoord = new TexCoord[countStatic];
	memcpy(triangle._texCoord, texCoordStatic, sizeof(TexCoord) * countStatic);
}

TexturePtr& Triangle::getTextureStatic() {
	if (!textureStatic) {
		textureStatic = Texture::getByName("Textures/Box.jpg");
	}

	return textureStatic;
}

Json::Value append(Triangle::Point* points, Triangle::TexCoord* texCoord, int& index, Triangle::Template& triangle)
{
	int intPtr = reinterpret_cast<int>(&triangle);
	const std::string stringPtr = std::to_string(intPtr);

	Json::Value templateJson;
	templateJson[stringPtr]["vector"].append(triangle.vector.x);
	templateJson[stringPtr]["vector"].append(triangle.vector.y);
	templateJson[stringPtr]["vector"].append(triangle.vector.z);
	templateJson[stringPtr]["scale"] = triangle.scale;
	templateJson[stringPtr]["dist"] = triangle.dist;
	templateJson[stringPtr]["index"] = index;

	for (int i = 0; i < 3; ++i)
	{
		templateJson[stringPtr]["points"].append(triangle.points[i].data[0]);
		templateJson[stringPtr]["points"].append(triangle.points[i].data[1]);
		templateJson[stringPtr]["points"].append(triangle.points[i].data[2]);
	}

	memcpy(points, &triangle.points, sizeof(Triangle::Point) * 3);
	memcpy(texCoord, &triangle.texCoord, sizeof(Triangle::TexCoord) * 3);
	index += 3;

	for (auto& child : triangle.childs) {
		Triangle::Point* pointPoints = &points[index];
		Triangle::TexCoord* pointTexCoord = &texCoord[index];
		templateJson[stringPtr]["childs"].append(append(pointPoints, pointTexCoord, index, child->getSelf()));
	}

	return templateJson;
};

void Triangle::make(Triangle& triangle, Template& templateTrianle)
{
	templateTrianle.make();
	int count = templateTrianle.getCount();

	triangle._count = count * 3;
	triangle._points = new Point[triangle._count * 10];
	triangle._texCoord = new TexCoord[triangle._count * 10];

	Json::Value jsonPoints;

	int iM = 0;
	for (int i = 0; i < triangle._count; ++i) {
		triangle._points[i].data[0] = iM;
		++iM;
		triangle._points[i].data[1] = iM;
		++iM;
		triangle._points[i].data[2] = iM;
		++iM;

		jsonPoints["empty"].append(triangle._points[i].data[0]);
		jsonPoints["empty"].append(triangle._points[i].data[1]);
		jsonPoints["empty"].append(triangle._points[i].data[2]);
	}

	int index = 0;
	Json::Value templateJson = append(triangle._points, triangle._texCoord, index, templateTrianle);

	help::saveJson("templateJson.json", templateJson, " ");

	for (int i = 0; i < triangle._count; ++i) {
		jsonPoints["setpo"].append(triangle._points[i].data[0]);
		jsonPoints["setpo"].append(triangle._points[i].data[1]);
		jsonPoints["setpo"].append(triangle._points[i].data[2]);
	}

	help::saveJson("jsonPoints.json", jsonPoints, " ");

	help::saveJson("templateJsonMake.json", templateJsonMake, " ");
	
}