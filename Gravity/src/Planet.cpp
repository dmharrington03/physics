#include "Header.hpp"

#define G 1

double Planet::ComputeDistance(sf::Vector2f pos1, sf::Vector2f pos2)
{
	// Pythagorean theorem
	return std::hypotf(std::abs(pos1.x - pos2.x), std::abs(pos1.y - pos2.y));
}

double Planet::UpdateForce(Planet* body, const Planet* sun, const float& dt)
{

	double deltaPMag = Planet::ComputeDistance(sun->getPosition(), body->getPosition());
	sf::Vector2f deltaP(sun->getPosition().x - body->getPosition().x, sun->getPosition().y - body->getPosition().y);
	long double force = deltaPMag != 0 ? G * sun->mass * body->mass / std::pow(deltaPMag, 2) : 0;

	// Normalize the vector
	deltaP.x /= deltaPMag;
	deltaP.y /= deltaPMag;

	// Change velocity by the force of gravity
	body->velocity = sf::Vector2f(body->velocity.x + force * deltaP.x * dt, body->velocity.y + force * deltaP.y * dt);
	return force;
}

void Planet::DoMotion(const float& dt)
{
	// Update position according to current velocity
	Planet::setPosition(Planet::getPosition() + Planet::velocity * dt);
	return;
}