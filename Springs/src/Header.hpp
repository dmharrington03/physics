void setEndpoints(sf::RectangleShape& line, sf::Vector2f a, sf::Vector2f b);

template <typename T>
void normalize(sf::Vector2<T>& vec)
{
	T mag = static_cast<T>(std::hypotf(vec.x, vec.y));
	vec.x /= mag;
	vec.y /= mag;
}