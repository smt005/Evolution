
#include "ShapeTriangles.h"
#include "glew/include/GL/glew.h"
#include <memory>

bool ShapeTriangles::initVBO()
{
	glDeleteBuffers(2, _buffer);
	glGenBuffers(2, _buffer);

	if (_countVertex == 0 || !_aVertex) {
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, _countVertex * 3 * sizeof(GLfloat), _aVertex, GL_STATIC_DRAW);

	if (_aTexCoord) {
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, _countVertex * 2 * sizeof(GLfloat), _aTexCoord, GL_STATIC_DRAW);
	}

	_hasVBO = true;
	return _hasVBO;
}

void ShapeTriangles::makeTriangle(ShapeTriangles& shape, const float& scale)
{
	static unsigned short countVertexStatic = 3;

	static float aVertexStatic[] = { 0.0f, 1.0f, 0.0f,
									-1.0f, -1.0f, 0.0f,
									1.0f, -1.0f, 0.0f };

	static float aTexCoordStatic[] = {	0.0f, 1.0f,
										1.0f, 0.0f,
										0.0f, 0.0f };
	

	shape._countVertex = countVertexStatic;

	{
		size_t count = countVertexStatic * 3;
		shape._aVertex = new float[count];

		for (int i = 0; i < count; ++i) {
			shape._aVertex[i] = aVertexStatic[i] * scale;
		}
	}

	{
		size_t count = countVertexStatic * 2;
		shape._aTexCoord = new float[count];

		for (int i = 0; i < count; ++i) {
			shape._aTexCoord[i] = aTexCoordStatic[i];
		}
	}
}

/*void ShapeTriangles::makePlane(ShapeTriangles& shape, const float& scale)
{
}*/
