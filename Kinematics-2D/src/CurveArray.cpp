std::vector<sf::Vector2f> createPointArray(sf::Vector2f vel, double g, double dt, double scaleFactor) {
	/* Creates and returns a list of relative coordinates according to
	a parametric function in terms of x and y */
	sf::Vector2f scaledVel(vel.x / scaleFactor, vel.y / scaleFactor);
	std::vector<sf::Vector2f> coords;
	coords.push_back(sf::Vector2f(0.0, 0.0));
	for (double t = 0.0, i = 0.0; t < (2 * scaledVel.y / -g); t += dt, i++)
	{
		t += dt;
		if ((int) i % 100 == 0)
			coords.push_back(sf::Vector2f(scaledVel.x * t, scaledVel.y * t + 0.5 * g * std::pow(t, 2)));
	}
	return coords;
}