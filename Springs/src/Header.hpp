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

	Ball() : vel(sf::Vector2f(0, 0)), stationary(false)
	{
		setPosition(0, 0);
		setRadius(20);
		setFillColor(sf::Color(134, 135, 181));
		setOrigin(20, 20);
	}

	void update(const float gravity=0.0005);
};

class Spring : public sf::RectangleShape
{
public:
	float rest_len;
	float spring_len;
	float k;
	Ball* a;
	Ball* b;

	Spring(float rest_len, float k, Ball* a, Ball* b)
		:  rest_len(rest_len), spring_len(rest_len), k(k), a(a), b(b)
	{
		setEndpoints(a->getPosition(), b->getPosition());
		setFillColor(sf::Color::Black);
	}

	Spring() : rest_len(100), spring_len(100), k(0.000005), a(nullptr), b(nullptr)
	{
		setEndpoints(sf::Vector2f(0, 0), sf::Vector2f(10, 10));
		setFillColor(sf::Color::Black);
	}

	void setEndpoints(sf::Vector2f a, sf::Vector2f b);
	void update();

	template <typename T>
	static void normalize(sf::Vector2<T>& vec);
};