#include <cstdlib>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;


static Texture jumpTexture;

void Jump::preload()
{
	jumpTexture = loadTexture("images/jump.png");
}

Jump::Jump()
{
	int n = rand();
	sprite.setTexture(jumpTexture);
}

void Jump::collide(Actor &actor)
{
	if (getBounds().intersects(actor.getBounds())) {
		actor.jump();
	}
}
