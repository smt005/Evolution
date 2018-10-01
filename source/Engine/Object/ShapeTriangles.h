#pragma once

class ShapeTriangles
{
public:
	inline unsigned short int countVertex() { return _countVertex; }
	inline const float* const aVertex() { return _aVertex; }
	inline const float* const aTexCoord() { return _aTexCoord; }

	inline bool hasVBO() { return _hasVBO; }
	inline unsigned int bufferVertexes() { return _buffer[0]; }
	inline unsigned int bufferTexCoords() { return _buffer[1]; }

	bool initVBO();

private:
	unsigned short int _countVertex = 0;
	float* _aVertex = nullptr;
	float* _aTexCoord = nullptr;

	bool _hasVBO = false;
	unsigned int _buffer[2];

public:
	static void makeTriangle(ShapeTriangles& shape, const float& scale = 1.0f);
	//static void makePlane(ShapeTriangles& shape, const float& scale = 1.0f);
};
