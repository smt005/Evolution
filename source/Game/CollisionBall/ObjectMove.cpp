
#include "ObjectMove.h"
#include <glm/fwd.hpp>

bool ObjectMove::colliding(ObjectMove& ball)
{
	float xd = getPos().x- ball.getPos().x;
	float yd = getPos().y - ball.getPos().y;

	float sumRadius = getRadius() + ball.getRadius();
	float sqrRadius = sumRadius * sumRadius;

	float distSqr = (xd * xd) + (yd * yd);

	if (distSqr <= sqrRadius) {
		return true;
	}

	return false;
}

void ObjectMove::resolveCollision(ObjectMove & ball)
{
	// get the mtd
	//glm::vec3 delta = getPos() - ball.getPos();
	glm::vec3 delta = ball.getPos() - getPos();
	float d = delta.length();
	// minimum translation distance to push balls apart after intersecting
	//glm::vec3 mtd = delta.multiply(((getRadius() + ball.getRadius()) - d) / d);

	glm::vec3 mtd = delta * (((getRadius() + ball.getRadius()) - d) / d);

	// resolve intersection --
	// inverse mass quantities
	float im1 = 1 / getMass();
	float im2 = 1 / ball.getMass();

	// push-pull them apart based off their mass
	//position = position.add(mtd.multiply(im1 / (im1 + im2)));
	glm::vec3 position = getPos() + (mtd * (im1 / (im1 + im2)));
	setPos(position);

	//ball.position = ball.position.subtract(mtd.multiply(im2 / (im1 + im2)));
	position = position - (mtd * (im2 / (im1 + im2)));
	setPos(position);

	// impact speed
	//Vector2d v = (this.velocity.subtract(ball.velocity));
	//float vn = v.dot(mtd.normalize());

	glm::vec3 v = vectorMove - ball.vectorMove;
	float vn = glm::dot(v, glm::normalize(mtd));

	// sphere intersecting but moving away from each other already
	if (vn > 0.0f) return;

	// collision impulse
	float Constants_restitution = 0.0f;
	float i = (-(1.0f + Constants_restitution) * vn) / (im1 + im2);
	//Vector2d impulse = mtd.multiply(i);
	glm::vec3 impulse = mtd * i;

	// change in momentum
	//this.velocity = this.velocity.add(impulse.multiply(im1));
	//ball.velocity = ball.velocity.subtract(impulse.multiply(im2));

	vectorMove = vectorMove + impulse * im1;
	ball.vectorMove = ball.vectorMove - impulse * im2;
}
