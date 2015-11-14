#include <cstdlib>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;


static Texture rocks[2];

void Rock::preload()
{
	rocks[0] = loadTexture("images/rock1.png");
	rocks[1] = loadTexture("images/rock2.png");
}

Rock::Rock()
{
	int n = rand();
	sprite.setTexture(rocks[n % 4], true);
	if (n & 16) sprite.scale(-1, 1);
}

void Rock::update(float deltaTime)
{
}

void Rock::collide(Actor &actor)
{
	if (getBounds().intersects(actor.getBounds())) {
		actor.knockHard();
	}
}
