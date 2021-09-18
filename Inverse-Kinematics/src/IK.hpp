class Point
{
public:

	sf::CircleShape shape;

	Point(sf::Vector2f initial_position, float radius, sf::Color color=sf::Color(100, 100, 100))
	{
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(initial_position);
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
		setEndpoints();
		shape.setFillColor(sf::Color(50, 50, 50));
	}

	Segment()
	{
		pa = nullptr;
		pb = nullptr;
	}

	void setEndpoints();
};

bool inRange(std::vector<Segment> &segList, int len, Point& p0, Point& pf);


template <typename T>
void normalize(sf::Vector2<T>& vec);

void fabrik(std::vector<Segment> &segList, int len, Point* pBegin, Point* pt);

void forwardPass(std::vector<Segment> &segList, int len, Point pEnd);
void backPass(std::vector<Segment> &segList, int len, Point pBegin);