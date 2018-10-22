#include <physics.h>

b2Vec2 pixel2meter(sf::Vector2f v)
{
	return b2Vec2(pixel2meter(v.x), pixel2meter(v.y));
}

float pixel2meter(float f)
{
	return f/pixelPerMeter;
}

sf::Vector2f meter2pixel(b2Vec2 v)
{
	return sf::Vector2f(meter2pixel(v.x), meter2pixel(v.y));
}

float meter2pixel(float f)
{
	return f*pixelPerMeter;
}
