#include "3DUtility.hpp"

sf::Vector2f rotatePoint(const sf::Vector2f &point, const float &theta)
{
	// Compute using 2D rotation matrix for angle theta in radius
	sf::Vector2f result;
	result.x = point.x * std::cosf(theta) - point.y * std::sinf(theta);
	result.y = point.x * std::sinf(theta) + point.y * std::cosf(theta);
	return result;
}


void rotate3z(sf::Vector3f &point, const float& theta)
{
	sf::Vector3f result;
	result.x = std::cosf(theta) * point.x + -std::sinf(theta) * point.y;
	result.y = std::sinf(theta) * point.x + std::cosf(theta) * point.y;
	result.z = point.z;

	point = result;
}

void rotate3x(sf::Vector3f &point, const float& theta)
{
	sf::Vector3f result;
	result.x = point.x;
	result.y = std::cosf(theta) * point.y + -std::sinf(theta) * point.z;
	result.z = std::sinf(theta) * point.y + std::cosf(theta) * point.z;

	point = result;
}

void rotate3y(sf::Vector3f &point, const float& theta)
{
	sf::Vector3f result;
	result.x = std::cosf(theta) * point.x + std::sinf(theta) * point.z;
	result.y = point.y;
	result.z = -std::sinf(theta) * point.x + std::cosf(theta) * point.z;

	point = result;
}

void setEndpoints(sf::RectangleShape &line, const sf::Vector2f a, const sf::Vector2f b)
{
	const float PI = 3.14159;

	line.setPosition(a);
	// Compute length of distance between points
	const float len = std::hypotf(b.x - a.x, b.y - a.y);
	line.setSize(sf::Vector2f(len, 2));

	// Compute the angle formed by the right triangle between the points, in degrees, correct for 0º straight down
	const float theta = std::atan2f(b.y - a.y, b.x - a.x) * 180 / PI;
	line.setRotation(theta);
}