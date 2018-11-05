
#include "glew/include/GL/glew.h"
#include <functional>

#include "Common/Help.h"
#include "FileManager.h"

#include "Triangle.h"

TexturePtr Triangle::textureStatic;

Triangle::~Triangle() {
	if (_points) {
		delete[] _points;
	}

	if (_texCoord) {
		delete[] _texCoord;
	}
}

void Triangle::setData(unsigned short int type, unsigned int count, Point* points, TexCoord* texCoord)
{
	type = _type;
	_count = count;
	_points = points;
	_texCoord = texCoord;
}

bool Triangle::initVBO() const
{
	unsigned int* buffer = const_cast<unsigned int*>(_buffer);

	glDeleteBuffers(2, buffer);
	glGenBuffers(2, buffer);

	if (_count == 0 || !_points) {
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, _count * 3 * sizeof(GLfloat), _points, GL_STATIC_DRAW);

	if (_texCoord) {
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, _count * 2 * sizeof(GLfloat), _texCoord, GL_STATIC_DRAW);
	}

	bool* hasVBO = const_cast<bool*>(&_hasVBO);
	*hasVBO = true;
	return _hasVBO;
}

// static
//	static

Triangle::Point Triangle::_pointsStatic[3] = { -0.425f, -0.9f, 0.0f,
												0.575f, 0.0f, 0.0f,
												-0.425f, 0.9f, 0.0f };

Triangle::TexCoord Triangle::_texCoordStatic[3] = { 1.715f, 0.0f,
													0.0f, 0.0f,
													0.0f, 1.715f };
unsigned int Triangle::_countPoint = 3;

TexturePtr& Triangle::getTextureStatic() {
	if (!textureStatic) {
		textureStatic = Texture::getByName("Textures/Box.jpg");
	}

	return textureStatic;
}

TrianglePtr Triangle::generateTriangle(const float radius)
{
	
	Point* points = new Point[3];
	TexCoord* texCoord = new TexCoord[3];

	float scale = 2.7f * radius;

	for (size_t i = 0; i < _countPoint; ++i) {
		points[i].data[0] = _pointsStatic[i].data[0] * scale;
		points[i].data[1] = _pointsStatic[i].data[1] * scale;
		points[i].data[2] = _pointsStatic[i].data[2] * scale;

		points[i].data[2] += 0.01f;
	}

	memcpy(texCoord, _texCoordStatic, sizeof(TexCoord) * 3);

	TrianglePtr triangle = TrianglePtr(new Triangle());
	triangle->setData(TRIANGLES, _countPoint, points, texCoord);

	return triangle;
}
