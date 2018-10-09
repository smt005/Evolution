
#include "glew/include/GL/glew.h"
#include <functional>

#include "Triangle.h"

TexturePtr textureStatic;

Triangle::~Triangle()
{
	if (_points) {
		delete[] _points;
	}
}

// Template

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
}

void Triangle::Template::make()
{
	makeData();

	for (const auto& item : childs) {
		item->makeData();
	}
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

void append(Triangle::Point* points, Triangle::TexCoord* texCoord, int& index, Triangle::Template& triangle)
{
	memcpy(points, triangle.points, sizeof(Triangle::Point) * 3);
	memcpy(texCoord, triangle.texCoord, sizeof(Triangle::TexCoord) * 3);
	index += 3;

	Triangle::Point* pointPoints = &points[index];
	Triangle::TexCoord* pointTexCoord = &texCoord[index];

	for (auto& child : triangle.childs) {
		append(pointPoints, pointTexCoord, index, child->getSelf());
	}
};

void Triangle::make(Triangle& triangle, Template& templateTrianle)
{
	templateTrianle.make();
	int count = templateTrianle.getCount();

	triangle._count = count * 3;
	triangle._points = new Point[triangle._count];
	triangle._texCoord = new TexCoord[triangle._count];

	int index = 0;
	append(triangle._points, triangle._texCoord, index, templateTrianle);
}