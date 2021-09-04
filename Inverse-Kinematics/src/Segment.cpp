#include "IK.hpp"

void Segment::setEndpoints(sf::Vector2f a, sf::Vector2f b)
{
	const float PI = 3.14159;
	shape.setPosition(a);
	// Compute length of distance between points
	const float len = std::hypotf(b.x - a.x, b.y - a.y);
	shape.setSize(sf::Vector2f(len, width));

	// Compute the angle formed by the right triangle between the points, in degrees, correct for 0º straight down
	const float theta = std::atan2f(b.y - a.y, b.x - a.x) * 180 / PI;
	shape.setRotation(theta);
}

template <typename T>
void normalize(sf::Vector2<T>& vec)
{
	T mag = static_cast<T>(std::hypotf(vec.x, vec.y));
	vec.x /= mag;
	vec.y /= mag;
}

bool inRange(Segment (&list)[], int len, Point& p0, Point& pf)
{
	// Add up the lengths of each segment and compare that with the distance to goal point
	int sum_len = 0;
	for (int i = 0; i < len - 1; i++)
	{
		// X dimension is long, Y is short
		sum_len += list[i].shape.getSize().x;
	}

	// Compare to actual distance (Pythagorean theorem)
	return sum_len > std::hypotf(p0.shape.getPosition().x - pf.shape.getPosition().x, p0.shape.getPosition().y - pf.shape.getPosition().y);
}

void backPass(Segment (&segList)[], int len, Point& pt)
{
	segList[len - 1].pb->shape.setPosition(pt.shape.getPosition());
	// Get vector between pb and pa, normalize
	// Mult by segment length
	// Move pa there, the setEndpoints of segment

	sf::Vector2f distanceAB(segList[len - 1].pb->shape.getPosition() - segList[len - 1].pa->shape.getPosition());
	normalize(distanceAB);

	// Multiply by original length of segment
	distanceAB = segList[len - 1].shape.getSize().x * distanceAB;
	segList[len - 1].pa->shape.setPosition(pt.shape.getPosition() - distanceAB);

}