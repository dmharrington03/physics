class Planet : public sf::CircleShape
{
	private:

		double mass;
		int radius;

	public:

		static double ComputeDistance(sf::Vector2f pos1, sf::Vector2f pos2);

		Planet(double m, int rad);
};