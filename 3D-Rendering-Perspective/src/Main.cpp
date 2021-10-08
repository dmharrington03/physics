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
	float s = 0.5;
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

	const int d = 2;

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

		for (int i = 0; i < 8; i++)
		{
			rotate3x(coords[i], 0.0005);
			rotate3y(coords[i], 0.0003);
			rotate3z(coords[i], 0.0007);
			sf::Vector2f cub(coords[i].x / (d - coords[i].z), coords[i].y / (d - coords[i].z));
			cub *= 600.f;
			sf::Vector2f newpos(center.x + cub.x, center.y - cub.y);
			points[i].setPosition(newpos);
			points[i].setRadius(radius + 0.2 * coords[i].z);
			points[i].setOrigin(points[i].getRadius(), points[i].getRadius());
		}

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
