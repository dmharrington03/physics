#include "Header.hpp"
#define G 0.1

double Planet::ComputeDistance(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::hypotf(std::abs(pos1.x - pos2.x), std::abs(pos1.y - pos2.y));
}

double Update(Planet* body, const Planet* sun, const float& dt)
{
	/* Update the velocity of each planet according to the force of gravity exerted on it by every
	other planet, calculated from Newton's Law of Gravitation */

	// Loop so all number of combinations of 2 planets are calculated (n choose 2)
	//* for now just do one
	// size_t listLen = list.size();
	// int sunMass = 10 + dt;

	// long double force = G * sunMass * list[0]->mass / std::pow(Planet::ComputeDistance(sun.getPosition(), list[0]->getPosition()), 2);
	// // TODO figure out direction vector to apply force to
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

void Planet::doMotion(const float& dt)
{
	Planet::setPosition(Planet::getPosition() + Planet::velocity * dt);
	return;
}