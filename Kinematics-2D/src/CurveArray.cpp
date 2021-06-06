std::vector<sf::Vector2f> createPointArray(sf::Vector2f vel, double g, double dt) {
	/* Creates and returns a list of relative coordinates according to
	a parametric function in terms of x and y */
	double t = 0.0;
	double scaleFactor = 50.0;
	sf::Vector2f scaledVel(vel.x / scaleFactor, vel.y / scaleFactor);
	std::vector<sf::Vector2f> coords;
	coords.push_back(sf::Vector2f(0.0, 0.0));
	while (!(coords.back().y < 0.0))
	{
		t += dt;
		coords.push_back(sf::Vector2f(scaledVel.x * t, scaledVel.y * t + 0.5 * g * std::pow(t, 2)));
	}
	return coords;
}