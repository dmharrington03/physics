#include "Header.hpp"

void setEndpoints(sf::RectangleShape& line, sf::Vector2f a, sf::Vector2f b)
{
	const float PI = 3.14159;
	line.setPosition(a);
	// Compute length of distance between points
	const float len = std::hypotf(b.x - a.x, b.y - a.y);
	line.setSize(sf::Vector2f(10, len));

	// Compute the angle formed by the right triangle between the points, in degrees, correct for 0º straight down
	const float theta = std::atan2f(b.y - a.y, b.x - a.x) * 180 / PI - 90;
	line.setRotation(theta);
}
