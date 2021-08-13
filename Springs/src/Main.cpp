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

	const float radius = 80.0;

	const int rest_len = 500;
	const float k = 0.0001;
	// const float gravity = 0.0005;

	Ball bob(radius, sf::Vector2f(width / 2, width / 2));
	Ball anchor(radius / 2, sf::Vector2f(width / 2, width / 2 - rest_len), true);

	Spring spring(rest_len, k, anchor, bob);

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

		// Main Logic -------------

		// spring_len = spring.getSize().y;
		// x = spring_len - rest_len;
		// force_mag = - k * x;
		// pos = ball.getPosition();

		// distance = sf::Vector2f(ball.getPosition().x - anchor.getPosition().x, ball.getPosition().y - anchor.getPosition().y);
		// normalize(distance);
		// force = distance * force_mag;

		// text.setString(std::to_string(force_mag));
		// force.y += gravity;

		// // Assume unit mass, F = ma becomes F = a
		// vel += force;
		// pos += vel;

		// ball.setPosition(pos);

		// setEndpoints(spring, anchor.getPosition(), ball.getPosition());

		// vel.x *= 0.999;
		// vel.y *= 0.999;


		spring.update();
		bob.update();
		anchor.update();
		// End Main Logic --------------

		window.clear(sf::Color(122, 80, 104));

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
			spring.setEndpoints(anchor.getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			bob.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			bob.vel = sf::Vector2f(0, 0);
		}


		window.draw(spring);
		window.draw(bob);
		window.draw(anchor);
		window.draw(text);
		window.display();

	}

	return 0;
}
