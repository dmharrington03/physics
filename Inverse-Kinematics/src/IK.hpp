class Point
{
private:

	bool is_locked;

public:

	sf::CircleShape shape;

	Point(sf::Vector2f initial_position, float radius, bool lock=false, sf::Color color=sf::Color(100, 100, 100))
	{
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(initial_position);

		is_locked = lock;
		if (is_locked)
			shape.setFillColor(sf::Color(160, 118, 133));
		else
			shape.setFillColor(color);
	}

	Point()
	{
		shape.setRadius(25);
		shape.setOrigin(25, 25);
		shape.setPosition(sf::Vector2f(0, 0));
		shape.setFillColor(sf::Color::White);
	}
};


class Segment
{
private:

	float width;

public:

	// Holds actual SFML shape class
	sf::RectangleShape shape;
	Point* pa;
	Point* pb;

	Segment(Point& a, Point& b)
	{
		width = 15;
		pa = &a;
		pb = &b;
		shape.setOrigin(0, width / 2);
		setEndpoints(a.shape.getPosition(), b.shape.getPosition());
		shape.setFillColor(sf::Color(50, 50, 50));
	}

	void setEndpoints(sf::Vector2f a, sf::Vector2f b);
};

bool inRange(Segment (&list)[], int len, Point& p0, Point& pf);


template <typename T>
void normalize(sf::Vector2<T>& vec);

void backPass(Segment (&segList)[], int len);
void forwardPass(Segment (&segList)[], int len);