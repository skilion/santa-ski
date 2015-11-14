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

FloatRect Entity::getBounds()
{
	return sprite.getGlobalBounds();
}
