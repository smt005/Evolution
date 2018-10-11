
#include "glew/include/GL/glew.h"
#include <functional>

#include "Common/Help.h"
#include "FileManager.h"
#include "Object/Texture.h"
#include "TriangleExample.h"


Json::Value templateJsonMake;
float height = 0.0001f;

void TriangleExample::Template::makeData()
{
	static const PointExample pointsStatic[] = { -0.425f, -0.9f, 0.0f,
		0.575f, 0.0f, 0.0f,
		-0.425f, 0.9f, 0.0f };

	static const TexCoordExample texCoordStatic[] = { 1.715f, 0.0f,
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
		pos.z += height;
		height += 0.0001f;

		for (unsigned int i = 0; i < 3; ++i) {
			points[i] += pos;
		}
	}

	memcpy(texCoord, texCoordStatic, sizeof(TexCoordExample) * 3);

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

void TriangleExample::Template::make()
{
	height = 0.0f;
	makeData();
}

// STATIC

Json::Value append(TriangleExample::PointExample* points, TriangleExample::TexCoordExample* texCoord, int& index, TriangleExample::Template& triangle)
{
	int intPtr = reinterpret_cast<int>(&triangle);
	const std::string stringPtr = std::to_string(intPtr);

	Json::Value templateJson;
	/*templateJson[stringPtr]["vector"].append(triangle.vector.x);
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
	}*/

	TriangleExample::PointExample* pointPoints = &points[index];
	TriangleExample::TexCoordExample* pointTexCoord = &texCoord[index];

	memcpy(pointPoints, &triangle.points, sizeof(TriangleExample::PointExample) * 3);
	memcpy(pointTexCoord, &triangle.texCoord, sizeof(TriangleExample::TexCoordExample) * 3);
	index += 3;

	for (auto& child : triangle.childs) {
		templateJson[stringPtr]["childs"].append(append(points, texCoord, index, child->getSelf()));
	}

	return templateJson;
};

void TriangleExample::make(Triangle& triangle, TriangleExample::Template& templateTrianle)
{
	templateTrianle.make();
	int count = templateTrianle.getCount();

	unsigned int countTemp = count * 3;
	TriangleExample::PointExample* pointsTemp = new TriangleExample::PointExample[countTemp * 10];
	TriangleExample::TexCoordExample* texCoordTemp = new TriangleExample::TexCoordExample[countTemp * 10];

	Json::Value jsonPoints;

	/*int iM = 0;
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
	}*/

	int index = 0;
	Json::Value templateJson = append(pointsTemp, texCoordTemp, index, templateTrianle);
	triangle.setData(Triangle::TRIANGLES, countTemp, (Triangle::Point*)pointsTemp, (Triangle::TexCoord*)texCoordTemp);

	/*help::saveJson("templateJson.json", templateJson, " ");

	for (int i = 0; i < triangle._count; ++i) {
	jsonPoints["setpo"].append(triangle._points[i].data[0]);
	jsonPoints["setpo"].append(triangle._points[i].data[1]);
	jsonPoints["setpo"].append(triangle._points[i].data[2]);
	}

	help::saveJson("jsonPoints.json", jsonPoints, " ");

	help::saveJson("templateJsonMake.json", templateJsonMake, " ");*/
}