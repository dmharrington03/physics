void rotate3z(sf::Vector3f &point, const float& theta);

void rotate3x(sf::Vector3f &point, const float& theta);

void rotate3y(sf::Vector3f &point, const float& theta);

void setEndpoints(sf::RectangleShape &line, const sf::Vector2f a, const sf::Vector2f b);

sf::Vector3f projectPoint(sf::Vector3f& point);

template <typename T>
T map(T in, T inMin, T inMax, T outMin, T outMax)
{
	T x = (in - inMin) / (inMax - inMin);
	T result = outMin + (outMax - outMin) * x;
	return result;
}