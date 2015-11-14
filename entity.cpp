#include "entities.hpp"
#include "global.hpp"
using namespace sf;

void Entity::draw()
{
	window->draw(sprite);
}
