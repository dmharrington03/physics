#include "IK.hpp"
#include "Platform/Platform.hpp"

int main()
{
	const int width = 1600;
	sf::RenderWindow window(sf::VideoMode(width, width), "Inverse Kinematics", sf::Style::Close);

	sf::RectangleShape axis(sf::Vector2f(width, 2));
	axis.setFillColor(sf::Color(50, 50, 50));
	axis.setOrigin(width / 2, 2);
	axis.setPosition(width / 2, width / 2);

	const int lines = 16;
	sf::RectangleShape gridline(sf::Vector2f(width, 1));
	gridline.setFillColor(sf::Color(50, 50, 50));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);

	Point p0(sf::Vector2f(width / 2 - 250, width / 2), 25, true);
	Point p1(sf::Vector2f(width / 2, width / 2), 25);
	Point p2(sf::Vector2f(width / 2 + 250, width / 2), 25);
	Point p3(sf::Vector2f(width / 2 + 500, width / 2), 25);

	Point pt(sf::Vector2f(width / 2 + 400, width / 2 - 200), 25, false, sf::Color(155, 180, 126));

	Segment seg0(p0, p1);
	Segment seg1(p1, p2);
	Segment seg2(p2, p3);

	Segment seg_list[] = {seg0, seg1, seg2};

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
		// Check if in range
		//* Backward pass
		//* Forward pass
		//* Loop # of iterations


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

		window.draw(seg0.shape);
		window.draw(seg1.shape);
		window.draw(seg2.shape);
		window.draw(p0.shape);
		window.draw(p1.shape);
		window.draw(p2.shape);
		window.draw(p3.shape);
		window.draw(pt.shape);
		window.display();
	}

	return 0;
}
