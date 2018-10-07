
#include "Triangle.h"

TexturePtr textureStatic;

Triangle::~Triangle()
{
	if (_points) {
		delete[] _points;
	}
}

// STATIC

void Triangle::makeTriangle(Triangle& triangle, const float& scale)
{
	static unsigned short int typeStatic = Triangle::TRIANGLES;
	static unsigned int countStatic = 3;
	static Point pointsStatic[] = { -0.425f, -0.9f, 0.0f,
									0.575f, 0.0f, 0.0f,
									-0.425f, 0.9f, 0.0f };

	static TexCoord _texCoordStatic[] = { 1.715f, 0.0f,
										0.0f, 0.0f,
										0.0f, 1.715f };

	triangle._type = typeStatic;
	triangle._count = countStatic;
	triangle._points = new Point[countStatic];

	for (unsigned int i = 0; i < countStatic; ++i) {
		triangle._points[i] = pointsStatic[i] * scale;
	}

	triangle._texCoord = new TexCoord[countStatic];
	memcpy(triangle._texCoord, _texCoordStatic, countStatic);
}

TexturePtr& Triangle::getTextureStatic() {
	if (!textureStatic) {
		textureStatic = Texture::getByName("Textures/Box.jpg");
	}

	return textureStatic;
}
