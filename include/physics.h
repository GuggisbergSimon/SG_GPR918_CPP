#ifndef PHYSICS_H
#define PHYSICS_H
#include "Box2D/Common/b2Math.h"
#include "SFML/System/Vector2.hpp"

const float pixelPerMeter = 100.0f;

b2Vec2 pixel2meter(sf::Vector2f v);
float pixel2meter(float f);

sf::Vector2f meter2pixel(b2Vec2 v);
float meter2pixel(float f);

#endif
