class Point
{
private:

	bool is_locked;

public:

	sf::CircleShape shape;

	Point(sf::Vector2f initial_position, float radius, bool lock=false)
	{
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(initial_position);

		is_locked = lock;
		if (is_locked)
			shape.setFillColor(sf::Color(160, 118, 133));
		else
			shape.setFillColor(sf::Color(100, 100, 100));
	}
};


class Segment
{
private:

	float width;

public:

	// Holds actual SFML shape class
	sf::RectangleShape shape;

	Segment(Point& a, Point& b)
	{
		width = 15;
		shape.setOrigin(0, width / 2);
		setEndpoints(a.shape.getPosition(), b.shape.getPosition());
		shape.setFillColor(sf::Color(50, 50, 50));
	}

	void setEndpoints(sf::Vector2f a, sf::Vector2f b);
};

bool inRange(Segment (&list)[], int len);