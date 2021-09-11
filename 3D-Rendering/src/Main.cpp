#include "Platform/Platform.hpp"
#include "3DUtility.hpp"

int main()
{
	const int width = 1600;
	sf::RenderWindow window(sf::VideoMode(width, width), "Kinematics", sf::Style::Close);

	sf::RectangleShape axis(sf::Vector2f(width, 6));
	axis.setFillColor(sf::Color(35, 35, 35));
	axis.setOrigin(width / 2, 2);
	axis.setPosition(width / 2, width / 2);

	const int lines = 16;
	sf::RectangleShape gridline(sf::Vector2f(width, 2));
	gridline.setFillColor(sf::Color(25, 25, 25));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);

	const int radius = 25;
	const sf::Vector2f center(width / 2, width / 2);
	// Origin at center coordinates
	sf::Vector2f p1(-100, 100);
	sf::Vector2f p2(100, 100);
	sf::Vector2f p3(100, -100);
	sf::Vector2f p4(-100, -100);

	sf::CircleShape point1(radius);
	point1.setOrigin(radius, radius);
	point1.setFillColor(sf::Color::White);
	point1.setPosition(center.x + p1.x, center.y - p1.y);

	sf::CircleShape point2(radius);
	point2.setOrigin(radius, radius);
	point2.setFillColor(sf::Color::White);
	point2.setPosition(center.x + p2.x, center.y - p2.y);

	sf::CircleShape point3(radius);
	point3.setOrigin(radius, radius);
	point3.setFillColor(sf::Color::White);
	point3.setPosition(center.x + p3.x, center.y - p3.y);

	sf::CircleShape point4(radius);
	point4.setOrigin(radius, radius);
	point4.setFillColor(sf::Color::White);
	point4.setPosition(center.x + p4.x, center.y - p4.y);

	double angle = 0.001;


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


		p1 = rotatePoint(p1, angle);
		p2 = rotatePoint(p2, angle);
		p3 = rotatePoint(p3, angle);
		p4 = rotatePoint(p4, angle);
		point1.setPosition(center.x + p1.x, center.y - p1.y);
		point2.setPosition(center.x + p2.x, center.y - p2.y);
		point3.setPosition(center.x + p3.x, center.y - p3.y);
		point4.setPosition(center.x + p4.x, center.y - p4.y);




		window.clear(sf::Color(15, 15, 15));

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

		window.draw(point1);
		window.draw(point2);
		window.draw(point3);
		window.draw(point4);
		window.display();
	}

	return 0;
}
