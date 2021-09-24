#include "Platform/Platform.hpp"
#include "3DUtility.hpp"
#define PI 3.14159

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

	const int radius = 20;
	float s = 150;
	const sf::Vector2f center(width / 2, width / 2);

	// Cube with side length s
	float initial_coords[8][3] =
	{
		{-s, -s, s}, {-s, -s, -s}, {s, -s, -s}, {s, -s, s},
		{-s, s, s}, {-s, s, -s}, {s, s, -s}, {s, s, s}
	};

	sf::Vector3f coords[8];
	sf::Vector3f projected[8];

	sf::CircleShape points[8];
	for (int i = 0; i < 8; i++)
	{
		coords[i].x = initial_coords[i][0];
		coords[i].y = initial_coords[i][1];
		coords[i].z = initial_coords[i][2];
		rotate3y(coords[i], PI / 4);
		rotate3x(coords[i], PI / 4 );
		points[i].setFillColor(sf::Color::White);
		points[i].setRadius(radius);
		points[i].setOrigin(radius, radius);
	}
	sf::RectangleShape side;
	side.setSize(sf::Vector2f(s, 2.0));
	side.setFillColor(sf::Color::White);
	side.setOrigin(0, 1);

	sf::Vector3f angle(0, 0, 0);
	sf::Vector3f prev_angle(0, 0, 0);




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

		// angle = std::atan2(sf::Mouse::getPosition(window).y, sf::Mouse::getPosition(window).x);
		// angle.x = map((double)sf::Mouse::getPosition(window).y, 0.0, (double)width, -1.5, 1.5);
		// angle.y = map((double)sf::Mouse::getPosition(window).x, 0.0, (double)width, -1.5, 1.5);
		// angle.z = map((double)std::hypot(angle.x, angle.y), 0.0, 2263.0, -1.0, 1.0);

		for (int i = 0; i < 8; i++)
		{
			// rotate3x(coords[i], 0.01);
			// rotate3y(coords[i], 0.001);
			// rotate3z(coords[i], angle.z - prev_angle.z);
			points[i].setPosition(center.x + coords[i].x, center.y - coords[i].y);
			//TODO set points
			// projected[i] = projectPoint(coords[i]);
			// points[i].setPosition(center.x + projected[i].x * 300, center.y - projected[i].y * 300);

		}

		prev_angle = angle;


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

		setEndpoints(side, points[0].getPosition(), points[1].getPosition());
		setEndpoints(side, points[1].getPosition(), points[2].getPosition());
		setEndpoints(side, points[2].getPosition(), points[3].getPosition());
		setEndpoints(side, points[3].getPosition(), points[0].getPosition());

		for (int i = 0; i < 4; i++)
		{
			setEndpoints(side, points[i].getPosition(), points[(i + 1) % 4].getPosition());
			window.draw(side);
			setEndpoints(side, points[i + 4].getPosition(), points[(i + 1) % 4 + 4].getPosition());
			window.draw(side);
			setEndpoints(side, points[i].getPosition(), points[i + 4].getPosition());
			window.draw(side);
		}

		for (int i = 0; i < 8; i++)
			window.draw(points[i]);

		window.display();
	}

	return 0;
}
