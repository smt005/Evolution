
#include "glew/include/GL/glew.h"
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

void Triangle::make(Triangle& triangle, Template& templateTrianle)
{
	templateTrianle.make();
	int count = templateTrianle.getCount();

	_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "LOG: Triangle::make %d\n", count);
}