#include "entities.hpp"
#include "global.hpp"
using namespace sf;


void Entity::draw()
{
	window->draw(sprite);
}

void Entity::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

const Vector2f &Entity::getPosition()
{
	return sprite.getPosition();
}

FloatRect Entity::getBounds()
{
	const int X = 8;
	FloatRect b = sprite.getGlobalBounds();
	b.left += X;
	b.top += X;
	b.width -= X * 2;
	b.height -= X * 2;
	return b;
}
