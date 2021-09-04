#include "IK.hpp"
#include "Platform/Platform.hpp"

int main()
{
	const int width = 1600;
	sf::RenderWindow window(sf::VideoMode(width, width), "Inverse Kinematics", sf::Style::Close);
	window.setMouseCursorVisible(false);

	sf::RectangleShape axis(sf::Vector2f(width, 2));
	axis.setFillColor(sf::Color(50, 50, 50));
	axis.setOrigin(width / 2, 2);
	axis.setPosition(width / 2, width / 2);

	const int lines = 16;
	sf::RectangleShape gridline(sf::Vector2f(width, 1));
	gridline.setFillColor(sf::Color(50, 50, 50));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);


	int N_SEG = 4;
	int N_POINTS = 5;
	const int spacing = 250;
	std::vector<Point> points;
	std::vector<Segment> segments;

	// Keep track of origin point
	Point pBegin(sf::Vector2f(width / 2 - spacing * 2, width / 2), 25);

	for (int i = 0; i < N_POINTS; i++)
		points.push_back(Point(sf::Vector2f(width / 2 + spacing * (i - 2), width / 2), 25));

	points[0].shape.setFillColor(sf::Color(160, 118, 133));

	Point pt(sf::Vector2f(width / 2 + 203, width / 2 - 242), 25, sf::Color(155, 180, 126));

	for (int i = 0; i < N_SEG; i++)
		segments.push_back(Segment(points[i], points[i + 1]));

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();

				default:
					continue;
			}
		}

		// TODO
		// * Space adds a new segment + point pair

		if (inRange(segments, N_SEG, pBegin, pt))
		{
			fabrik(segments, N_SEG, &pBegin, &pt);
		}
		else
		{
			// Solve for the farthest possible point in direction of pt
			float segmentSum = 0;
			for (int i = 0; i < N_SEG; i++)
				segmentSum += segments[i].shape.getSize().x;

			sf::Vector2f totalDisplacement(pt.shape.getPosition() - pBegin.shape.getPosition());
			normalize(totalDisplacement);
			totalDisplacement = segmentSum * totalDisplacement;
			Point pInDirection(pBegin.shape.getPosition() + totalDisplacement, 25);

			fabrik(segments, N_SEG, &pBegin, &pInDirection);
		}

		pt.shape.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));


		window.clear(sf::Color(127, 158, 176));

		window.draw(axis);
		axis.setRotation(90);
		window.draw(axis);
		axis.setRotation(0);

		for (int i = 0; i < lines; i++)
		{
			gridline.setRotation(0);
			gridline.setPosition(width / 2, i * (width / lines));
			window.draw(gridline);
			gridline.setRotation(90);
			gridline.setPosition(i * (width / lines), width / 2);
			window.draw(gridline);
		}

		for (int i = 0; i < N_SEG; i++)
			window.draw(segments[i].shape);

		for (int i = 0; i < N_POINTS; i++)
			window.draw(points[i].shape);

		window.draw(pt.shape);
		window.display();
	}

	return 0;
}
