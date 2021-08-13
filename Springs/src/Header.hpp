class Ball : public sf::CircleShape
{
public:
	sf::Vector2f vel;
	bool stationary;

	Ball(const float& radius, const sf::Vector2f& initial_pos, bool stationary=false)
		: vel(sf::Vector2f(0, 0)), stationary(stationary)
	{
		setPosition(initial_pos);
		setRadius(radius);
		setFillColor(sf::Color(134, 135, 181));
		setOrigin(radius, radius);
	}

	void update();
};

class Spring : public sf::RectangleShape
{
public:
	const float rest_len;
	float spring_len;
	const float& k;
	Ball& a;
	Ball& b;

	Spring(const float& rest_len, const float& k, Ball& a, Ball& b)
		:  rest_len(rest_len), spring_len(rest_len), k(k), a(a), b(b)
	{
		setEndpoints(a.getPosition(), b.getPosition());
		setFillColor(sf::Color::Black);
	}

	void setEndpoints(sf::Vector2f a, sf::Vector2f b);
	void update(const float gravity=0.0005);

	template <typename T>
	static void normalize(sf::Vector2<T>& vec);
};