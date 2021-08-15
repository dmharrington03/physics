#include "Header.hpp"


void Spring::setEndpoints(sf::Vector2f a, sf::Vector2f b)
{
	const float PI = 3.14159;
	setPosition(a);
	// Compute length of distance between points
	const float len = std::hypotf(b.x - a.x, b.y - a.y);
	setSize(sf::Vector2f(5, len));

	// Compute the angle formed by the right triangle between the points, in degrees, correct for 0º straight down
	const float theta = std::atan2f(b.y - a.y, b.x - a.x) * 180 / PI - 90;
	setRotation(theta);
}

template <typename T>
void Spring::normalize(sf::Vector2<T>& vec)
{
	T mag = static_cast<T>(std::hypotf(vec.x, vec.y));
	vec.x /= mag;
	vec.y /= mag;
}

void Spring::update()
{
	float del_x = a->getPosition().x - b->getPosition().x;
	float del_y = a->getPosition().y - b->getPosition().y;

	sf::Vector2f distance(del_x, del_y);
	spring_len = std::hypotf(del_x, del_y);

	normalize(distance);

	// F = -k * x
	float force_mag = - k * (spring_len - rest_len);
	sf::Vector2f force;
	force.x = distance.x * force_mag;
	force.y = distance.y * force_mag;

	// F = ma, assuming unit mass F = a
	a->vel += force;
	b->vel += force * -1.f;

	setEndpoints(a->getPosition(), b->getPosition());
}

void Ball::update(const float gravity)
{
	// Gravity
	vel.y += gravity;

	// Air resistance, dampening
	vel.x *= 0.999;
	vel.y *= 0.999;

	if (!stationary)
		setPosition(getPosition() + vel);

}