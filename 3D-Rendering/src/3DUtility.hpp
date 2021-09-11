sf::Vector2f rotatePoint(const sf::Vector2f &point, const float &theta)
{
	// Compute using 2D rotation matrix for angle theta in radius
	sf::Vector2f result;
	result.x = point.x * std::cosf(theta) - point.y * std::sinf(theta);
	result.y = point.x * std::sinf(theta) + point.y * std::cosf(theta);
	return result;
}