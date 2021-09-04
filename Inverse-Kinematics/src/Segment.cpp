#include "IK.hpp"

void Segment::setEndpoints()
{
	const float PI = 3.14159;
	sf::Vector2f a_pos(pa->shape.getPosition());
	sf::Vector2f b_pos(pb->shape.getPosition());

	shape.setPosition(pa->shape.getPosition());
	// Compute length of distance between points
	const float len = std::hypotf(b_pos.x - a_pos.x, b_pos.y - a_pos.y);
	shape.setSize(sf::Vector2f(len, width));

	// Compute the angle formed by the right triangle between the points, in degrees, correct for 0º straight down
	const float theta = std::atan2f(b_pos.y - a_pos.y, b_pos.x - a_pos.x) * 180 / PI;
	shape.setRotation(theta);
}

template <typename T>
void normalize(sf::Vector2<T>& vec)
{
	T mag = static_cast<T>(std::hypotf(vec.x, vec.y));
	vec.x /= mag;
	vec.y /= mag;
}

bool inRange(std::vector<Segment> &segList, int len, Point& p0, Point& pf)
{
	// Add up the lengths of each segment and compare that with the distance to goal point
	int sum_len = 0;
	for (int i = 0; i < len; i++)
	{
		// X dimension is long, Y is short
		sum_len += segList[i].shape.getSize().x;
	}

	// Compare to actual distance (Pythagorean theorem)
	return sum_len > std::hypotf(pf.shape.getPosition().x - p0.shape.getPosition().x, pf.shape.getPosition().y - p0.shape.getPosition().y);

}

void backPass(std::vector<Segment> &segList, int listLen, Point pEnd)
{
	Point *pt = &pEnd;
	// Loop backwards through the list
	for (int i = listLen - 1; i >= 0; i--)
	{
		// Calculate displacement vector between Target and pA
		sf::Vector2f distanceTA(segList[i].pa->shape.getPosition() - pt->shape.getPosition());
		normalize(distanceTA);

		// Multiply by original length of segment
		float segLength = segList[i].shape.getSize().x;

		distanceTA = segLength * distanceTA;

		// Move B to T, move A to the length of the segment away from T, in the same direction
		segList[i].pb->shape.setPosition(pt->shape.getPosition());
		segList[i].pa->shape.setPosition(pt->shape.getPosition() + distanceTA);

		// Update endpoints of each segment rectShape
		segList[i].setEndpoints();

		// Update the target for the next segment's pass
		pt = segList[i].pa;
	}
}


void forwardPass(std::vector<Segment> &segList, int len, Point pBegin)
{
	Point *pt = &pBegin;
	// Loop fowards through the list
	for (int i = 0; i < len; i++)
	{
		// Calculate displacement vector between Target and pB
		sf::Vector2f distanceTA(segList[i].pb->shape.getPosition() - pt->shape.getPosition());
		normalize(distanceTA);

		// Multiply by original length of segment
		float segLength = segList[i].shape.getSize().x;

		distanceTA = segLength * distanceTA;

		// Move B to T, move A to the length of the segment away from T, in the same direction
		segList[i].pa->shape.setPosition(pt->shape.getPosition());
		segList[i].pb->shape.setPosition(pt->shape.getPosition() + distanceTA);

		// Update endpoints of each segment rectShape
		segList[i].setEndpoints();

		// Update the target for the next segment's pass
		pt = segList[i].pb;
	}
}

void fabrik(std::vector<Segment> &segList, int len, Point* pBegin, Point* pt)
{
	float deltaX = segList[len - 1].pb->shape.getPosition().x - pt->shape.getPosition().x;
	float deltaY = segList[len - 1].pb->shape.getPosition().y - pt->shape.getPosition().y;

	while (std::hypotf(deltaX, deltaY) > 1)
	{
		deltaX = segList[len - 1].pb->shape.getPosition().x - pt->shape.getPosition().x;
		deltaY = segList[len - 1].pb->shape.getPosition().y - pt->shape.getPosition().y;
		backPass(segList, len, *pt);
		forwardPass(segList, len, *pBegin);
	}
}