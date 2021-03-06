#include "Platform/Platform.hpp"
#include "Header.hpp"

//TODO Cleanup, add paths, to scale
// writing this from my chromebook
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
	text.setString("Hello World");

	Planet sun(sf::Vector2f(width / 2, width / 2), 1000.0, 50.0);
	Planet earth(sf::Vector2f(width / 2, width / 2 + 400), 1.0, 30.0);
	Planet mars(sf::Vector2f(width / 2, width / 2 + 600), 1.0, 30.0);
	earth.setFillColor(sf::Color(30, 60, 250));
	mars.setFillColor(sf::Color(150, 80, 50));

	// Initial tangential velocity
	earth.velocity = sf::Vector2f(1.5, 0);
	mars.velocity = sf::Vector2f(1.3, 0);

	sf::RectangleShape axis(sf::Vector2f(width, 6));
	axis.setFillColor(sf::Color(150, 150, 150));
	axis.setOrigin(width / 2, 2);
	axis.setPosition(width / 2, width / 2);

	const int lines = 16;
	sf::RectangleShape gridline(sf::Vector2f(width, 2));
	gridline.setFillColor(sf::Color(80, 80, 80));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);

	const double dt = 0.1;


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

		Planet::UpdateForce(&mars, &sun, dt);
		text.setString(std::to_string(Planet::UpdateForce(&earth, &sun, dt)) + "\n" + std::to_string(earth.velocity.y));

		earth.DoMotion(dt);
		mars.DoMotion(dt);


		window.clear(sf::Color(50, 50, 50));

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

		window.draw(text);
		window.draw(earth);
		window.draw(mars);
		window.draw(sun);
		window.display();
	}

	return 0;
}
