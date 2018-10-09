#pragma once

#include <vector>

#include "Position.h"
#include "Texture.h"

class Triangle : public Position
{
public:
	struct Point {
		float data[3] = { 0.0f, 0.0f, 0.0f };
		Point& operator*(const float scale) {
			data[0] *= scale;
			data[1] *= scale;
			data[2] *= scale;
			return *this;
		}
		Point& operator+=(const glm::vec3& pos) {
			data[0] += pos.x;
			data[1] += pos.y;
			data[2] += pos.z;
			return *this;
		}
	};
	
	struct TexCoord {
		float data[2] = { 0.0f, 0.0f };
	};

	enum
	{
		NONE = 0x0000,
		TRIANGLES = 0x0004,
		STRIP = 0x0005,
		FAN = 0x0006
	};

public:
	Triangle()
		: _count(0)
		, _points(nullptr)
		, _texCoord(nullptr)
	{}
	~Triangle();

	inline void set(const TexturePtr& texture)				{ _texture = texture; }
	inline Triangle& operator=(const TexturePtr& texture)	{ _texture = texture; }
	inline void setTexture(const std::string& name)			{ _texture = Texture::getByName(name); }

	Texture& texture();
	unsigned int textureId() {
		if (_texture) return _texture->id();
		_texture = getTextureStatic();
		return _texture->id();
	}

	const Triangle& getSelf() const { return *this; }

	inline unsigned short int countVertex() { return _count * 3; }
	inline const float* const aVertex() { return (float*)_points; }
	inline const float* const aTexCoord() { return (float*)_texCoord; }

	inline bool hasVBO() { return _hasVBO; }
	inline unsigned int bufferVertexes() { return _buffer[0]; }
	inline unsigned int bufferTexCoords() { return _buffer[1]; }

	bool initVBO();

private:
	unsigned short int _type;	//	GL_TRIANGLES 0x0004, GL_TRIANGLE_STRIP 0x0005, GL_TRIANGLE_FAN 0x0006
	unsigned int _count;
	Point* _points;
	TexCoord* _texCoord;
	TexturePtr _texture;

	bool _hasVBO = false;
	unsigned int _buffer[2];

public:
	struct Template;
	typedef std::shared_ptr<Template> TemplatePtr;

	struct Template
	{
		glm::vec3 vector;
		float dist;
		float scale;
		std::vector<TemplatePtr> childs;

		Template* parent;
		glm::vec3 pos;
		Point points[3];
		TexCoord texCoord[3];

		Template& getSelf() { return *this; }

		Template()
			: parent(nullptr)
			, dist(0.0f)
			, scale(1.0f)
			, pos(glm::vec3(0.0f))
		{}

		Template& add(const float distToParent, const float scaleTo, const glm::vec3& vectorToParent) {
			Template* t = new Template();
			TemplatePtr tPtr = TemplatePtr(t);
				tPtr->parent = this;
				tPtr->dist = distToParent;
				tPtr->scale = scaleTo;
				tPtr->vector = vectorToParent;
			childs.push_back(tPtr);
			return *t;
		}

		int getCount() {
			int count = 1;
			for (const auto& item : childs) {
				count += item->getCount();
			}
			return count;
		}

		void makeData();
		void make();
	};

	static void makeTriangle(Triangle& triangle, const float& scale = 1.0f);
	static TexturePtr& getTextureStatic();
	static void make(Triangle& triangle, Template& templateTrianle);
};
