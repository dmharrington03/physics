#include "Platform/Platform.hpp"

int main()
{
	const int width = 1600;
	sf::RenderWindow window(sf::VideoMode(width, width), "Kinematics", sf::Style::Default);

	sf::Font font;
	if (!font.loadFromFile("Roboto Mono Medium for Powerline.ttf"))
		std::cout << "Error loading font" << std::endl;

	sf::Text valuesText;
	valuesText.setFont(font);
	valuesText.setCharacterSize(50);
	valuesText.setFillColor(sf::Color(20, 20, 20));
	valuesText.setPosition(20, 20);

	sf::Text mathText;
	mathText.setFont(font);
	mathText.setCharacterSize(40);
	mathText.setFillColor(sf::Color(20, 20, 20));
	mathText.setPosition(20, 1200);

	const float radius = 80.0;
	sf::CircleShape ball(radius);
	ball.setFillColor(sf::Color(40, 155, 90));
	ball.setOrigin(sf::Vector2f(radius, radius));
	ball.setPosition(sf::Vector2f(100, width / 2));

	sf::RectangleShape axis(sf::Vector2f(width, 6));
	axis.setFillColor(sf::Color(40, 40, 40));
	axis.setOrigin(width / 2, 2);
	axis.setPosition(width / 2, width / 2);

	const int lines = 16;
	sf::RectangleShape gridline(sf::Vector2f(width, 2));
	gridline.setFillColor(sf::Color(40, 40, 40));
	gridline.setOrigin(width / 2, 1);
	gridline.setPosition(0, width / 2);

	double dt = 0.01;
	double v = 0.0;
	double a = 0.0;
	double x = 0.0;
	double dx;
	double dv;

	// Math expression text strings
	std::string vExp;
	std::string aExp;
	std::string xExp;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			ball.setPosition(width / 2, width / 2);
			v = 0.0;
			a = 0.0;
			x = 0.0;
		}

		// User input for changing acceleration
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			a += -0.1 * dt;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			a += 0.1 * dt;

		// ---- Kinematics Logic ----- //
		dv = a * dt;
		dx = v * dt;

		vExp = "v = dx/dt = " + std::to_string(dx).substr(0, 5) + "/" + std::to_string(dt).substr(0, 4) + " = " + std::to_string(dx / dt).substr(0, 5);
		v += dv;

		xExp = "x1 = x0 + vdt = " + std::to_string(x).substr(0, 4) + " + " + std::to_string(v).substr(0, 4) + " * " + std::to_string(dt).substr(0, 4) + " = " + std::to_string(x + dx).substr(0, 5);
		x += dx;
		ball.setPosition(x + (width / 2), width / 2);
		// ----- ----- //

		aExp = "a = dv/dt = " + std::to_string(dv).substr(0, 6) + "/" + std::to_string(dt).substr(0, 4) + " = " + std::to_string(dv / dt).substr(0, 5);
		mathText.setString(xExp + '\n' + vExp + '\n' + aExp);
		valuesText.setString("Acceleration: " + std::to_string(a).substr(0, 5) + "\nVelocity: " + std::to_string(v).substr(0, 5) + "\nPosition: " + std::to_string(x).substr(0, 6));

		window.clear(sf::Color(230, 230, 230));

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

		window.draw(valuesText);
		window.draw(mathText);
		window.draw(ball);
		window.display();
	}

	return 0;
}
