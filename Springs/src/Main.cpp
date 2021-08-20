#include "Header.hpp"
#include "Platform/Platform.hpp"


int main()
{
	const int width = 1600;
	sf::RenderWindow window(sf::VideoMode(width, width), "Kinematics", sf::Style::Close);

	sf::Font font;
	if (!font.loadFromFile("Roboto Mono Medium for Powerline.ttf"))
		std::cout << "Error loading font" << std::endl;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setPosition(20, 20);

	const float radius = 20.0;
	const int nPoints = 7;
	const float rest_len = 150;
	const float k = 0.000050;
	const float gravity = 0.0005;

	Ball point_array[nPoints];
	Spring spring_array[nPoints - 1];

	for (int i = 0; i < nPoints; i++)
		point_array[i] = Ball(radius, sf::Vector2f(width / 2, 200 + rest_len * i));

	point_array[0].stationary = true;

	for (int i = 0; i < nPoints - 1; i++)
		spring_array[i] = Spring(rest_len, k, &point_array[i], &point_array[i + 1]);


	sf::RectangleShape axis(sf::Vector2f(width, 6));
	axis.setFillColor(sf::Color(87, 55, 73));
	axis.setOrigin(width / 2, 2);
	axis.setPosition(width / 2, width / 2);

	const int lines = 16;
	sf::RectangleShape gridline(sf::Vector2f(width, 2));
	gridline.setFillColor(sf::Color(87, 55, 73));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);

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


		window.clear(sf::Color(153, 99, 130));


		for (int i = 0; i < nPoints - 1; i++)
			spring_array[i].update();

		for (int i = 0; i < nPoints; i++)
			point_array[i].update(gravity);

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			spring_array[nPoints - 2].setEndpoints(point_array[nPoints - 2].getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			point_array[nPoints - 1].setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			point_array[nPoints - 1].vel = sf::Vector2f(0, 0);
		}


		for (int i = 0; i < nPoints; i++)
			window.draw(point_array[i]);

		for (int i = 0; i < nPoints - 1; i++)
			window.draw(spring_array[i]);

		window.draw(text);
		window.display();

	}

	return 0;
}
