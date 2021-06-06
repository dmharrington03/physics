#include "Headers.hpp"
#define PI 3.141592

int main()
{
	const int width = 1600;
	sf::RenderWindow window(sf::VideoMode(width, width), "Kinematics-2D", sf::Style::Close);

	sf::Font font;
	if (!font.loadFromFile("Roboto Mono Medium for Powerline.ttf"))
		std::cout << "Error loading font" << std::endl;

	sf::Text text1;
	text1.setFont(font);
	text1.setCharacterSize(50);
	text1.setFillColor(sf::Color::White);
	text1.setPosition(20, 20);
	text1.setString("Adjust the ball's trajectory with your cursor,\nthen click to launch");

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(50);
	text2.setFillColor(sf::Color::White);
	text2.setPosition(20, 175);

	sf::Text textX;
	textX.setFont(font);
	textX.setCharacterSize(50);
	textX.setFillColor(sf::Color::White);


	sf::Text textY;
	textY.setFont(font);
	textY.setCharacterSize(50);
	textY.setFillColor(sf::Color::White);

	const int lines = 16;
	double theta = 0.0;
	double trajectoryMagnitude;
	const float radius = 50.0;
	sf::Vector2f origin(width / lines, width - width / lines - radius);
	sf::Vector2i mousePos;
	sf::Vector2f vComponents;

	sf::CircleShape ball(radius);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(radius, radius);
	ball.setPosition(origin);

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

	std::vector<sf::Vector2f> trajectoryCurve;
	sf::Vector2f ballVelocity(0.0, 0.0);
	double dt = 0.02;
	double g = -0.5; // Gravitational acceleration
	double scaleFactor = 50.0; // Scale down velocity for animation
	bool isMoving = false;

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
		if (!isMoving)
		{
			vComponents = sf::Vector2f(mousePos.x - width / lines, width - mousePos.y - width / lines);
			theta = (180 / PI) * (float) std::atan2(width - mousePos.y, mousePos.x);
		}

		trajectoryMagnitude = std::hypot(vComponents.x, vComponents.y) * 0.25;

		// Returns array of points on the trajectory curve
		trajectoryCurve = createPointArray(vComponents, g, dt, scaleFactor);

		trajectory.setRotation(-theta);
		trajectory.setSize(sf::Vector2f(trajectoryMagnitude, 6));

		xComp.setSize(sf::Vector2f(trajectoryMagnitude * std::cos(theta * PI / 180), 6));
		yComp.setSize(sf::Vector2f(6, trajectoryMagnitude * std::sin(theta * PI / 180)));
		yComp.setPosition(origin.x + xComp.getSize().x, width - width / lines - radius);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ball.setPosition(origin);
			ballVelocity.x = vComponents.x / scaleFactor;
			ballVelocity.y = -vComponents.y / scaleFactor;
			isMoving = true;
		}
		if (isMoving)
		{
			ballVelocity.y += -g * dt;
			ball.setPosition(ball.getPosition().x + ballVelocity.x * dt, ball.getPosition().y + ballVelocity.y * dt);
			if (ball.getPosition().y > width - (width / lines) - radius)
				isMoving = false;
		}

		text2.setString(
			"Equations of motion:\n"
			"x(t) = " + std::to_string(vComponents.x / scaleFactor).substr(0, 4) + "t\n"
			"y(t) = " + std::to_string(vComponents.y / scaleFactor).substr(0, 4) + "t + 0.5 * "
			+ std::to_string(g).substr(0, 4) + " * t^2"
		);
		textX.setString(std::to_string(vComponents.x / scaleFactor).substr(0, 4));
		textY.setString(std::to_string(vComponents.y / scaleFactor).substr(0, 4));

		// Position velocity component labels in the center of their respective lines
		textY.setPosition(yComp.getPosition().x + 20, yComp.getPosition().y - yComp.getSize().y / 2);
		textX.setPosition(xComp.getPosition().x + xComp.getSize().x / 2, xComp.getPosition().y + 50);

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

		// Draw trajectory curve
		for (int i = 0; i < (int) trajectoryCurve.size(); i++)
		{
			sf::CircleShape point(10);
			point.setOrigin(10, 10);
			if (i * 4 < 200)
				point.setFillColor(sf::Color(255 - i * 4, 0, 255 - i * 4));
			else
				point.setFillColor(sf::Color(50, 0, 50));
			point.setPosition(origin.x + trajectoryCurve[i].x, origin.y - trajectoryCurve[i].y);
			window.draw(point);
		}

		window.draw(text1);
		window.draw(text2);
		window.draw(textX);
		window.draw(textY);
		window.draw(ball);
		window.draw(trajectory);
		window.draw(xComp);
		window.draw(yComp);
		window.display();
	}

	return 0;
}
