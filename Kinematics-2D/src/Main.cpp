#include "Platform/Platform.hpp"

#define PI 3.141592

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

	const float radius = 50.0;
	const int lines = 16;
	double theta = 0.0;
	double trajectoryMagnitude;
	sf::Vector2i mousePos;
	sf::Vector2f vComponents;

	sf::CircleShape ball(radius);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(radius, radius);
	ball.setPosition(width / lines, width - width / lines - radius);

	sf::RectangleShape axis(sf::Vector2f(width, 6));
	axis.setFillColor(sf::Color(150, 150, 150));
	axis.setOrigin(width / lines, 2);
	axis.setPosition(width / lines, width - width / lines);

	sf::RectangleShape gridline(sf::Vector2f(width, 2));
	gridline.setFillColor(sf::Color(120, 120, 120));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);

	sf::RectangleShape trajectory(sf::Vector2f(400, 6));
	trajectory.setFillColor(sf::Color::Red);
	trajectory.setOrigin(0, 3);
	trajectory.setPosition(ball.getPosition());

	sf::RectangleShape xComp(sf::Vector2f(400, 6));
	xComp.setFillColor(sf::Color::Green);
	xComp.setOrigin(0, 3);
	xComp.setPosition(ball.getPosition());

	sf::RectangleShape yComp(sf::Vector2f(6, 400));
	yComp.setFillColor(sf::Color::Cyan);
	yComp.setOrigin(3, 0);
	yComp.setPosition(ball.getPosition());
	yComp.setRotation(180);

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

		mousePos = sf::Mouse::getPosition(window);
		vComponents = sf::Vector2f(mousePos.x - width / lines, width - mousePos.y - width / lines);
		trajectoryMagnitude = std::hypot(vComponents.x, vComponents.y) * 0.25;

		//TODO /* ಥ﹏ಥ */ fix angle

		theta = (180 / PI) * (float) std::atan2(width - mousePos.y, mousePos.x);
		text.setString("Theta" + std::to_string(theta));
		trajectory.setRotation(-theta);
		trajectory.setSize(sf::Vector2f(trajectoryMagnitude, 6));

		// xComp.setPosition(mousePos.x, width - width / lines);
		xComp.setSize(sf::Vector2f(trajectoryMagnitude * std::cos(theta * PI / 180), 6));
		yComp.setSize(sf::Vector2f(6, trajectoryMagnitude * std::sin(theta * PI / 180)));
		yComp.setPosition(ball.getPosition().x + xComp.getSize().x ,width - width / lines - radius);
		// yComp.setPosition(width - width / lines, mousePos.y);

		window.clear(sf::Color(50, 50, 70));

		window.draw(axis);
		axis.setRotation(-90);
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
		window.draw(ball);
		window.draw(trajectory);
		window.draw(xComp);
		window.draw(yComp);
		window.display();
	}

	return 0;
}
