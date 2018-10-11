#pragma once

#include <vector>
#include "jsoncpp/include/json/json.h"

#include "Object/Triangle.h"

class TriangleExample : public Triangle
{
public:
	struct PointExample {
		float data[3] = { 0.0f, 0.0f, 0.0f };
		PointExample& operator*(const float scale) {
			data[0] *= scale;
			data[1] *= scale;
			data[2] *= scale;
			return *this;
		}
		PointExample operator*(const float scale) const {
			PointExample temp;
			temp.data[0] = data[0] * scale;
			temp.data[1] = data[1] * scale;
			temp.data[2] = data[2] * scale;
			return temp;
		}
		PointExample& operator+=(const glm::vec3& pos) {
			data[0] += pos.x;
			data[1] += pos.y;
			data[2] += pos.z;
			return *this;
		}
	};

	struct TexCoordExample {
		float data[2] = { 0.0f, 0.0f };
	};

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
		PointExample points[3];
		TexCoordExample texCoord[3];

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

	static void make(Triangle& triangle, Template& templateTrianle);
};
