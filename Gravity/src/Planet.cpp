class Planet
{
	private:

		double mass;
		int radius;

	public:

		double ComputeDistance(sf::Vector2f pos1, sf::Vector2f pos2);

		Planet(double m, int rad);
		~Planet();
};

Planet::Planet(double m, int rad)
{
	Planet::mass = m;
	Planet::radius = rad;
}

Planet::~Planet()
{
}

double ComputeDistance(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::hypotf(std::abs(pos1.x - pos2.x), std::abs(pos1.y - pos2.y));
}
