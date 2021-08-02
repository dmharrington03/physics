class Planet : public sf::CircleShape
{
	public:

		sf::Vector2f velocity;
		double mass;
		static double ComputeDistance(const sf::Vector2f pos1, const sf::Vector2f pos2);

		void doMotion(const float& dt);

		Planet(const sf::Vector2f pos, const double m, const int rad) : sf::CircleShape(rad), velocity(0, 0), mass(m)
		{
			Planet::setPosition(pos);
			Planet::setFillColor(sf::Color(245, 225, 70));
			Planet::setOrigin(sf::Vector2f(Planet::getRadius(), Planet::getRadius()));
			std::cout << Planet::mass;
		};
};

double Update(Planet* body, const Planet* sun, const float& dt);