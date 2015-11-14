#include <cstdlib>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;


static Texture dunes[3];

void Dune::preload()
{
	dunes[0] = loadTexture("images/dune1.png");
	dunes[1] = loadTexture("images/dune2.png");
	dunes[2] = loadTexture("images/dune3.png");
}

Dune::Dune()
{
	int n = rand();
	sprite.setTexture(dunes[n % 3], true);
	if (n & 16) sprite.scale(-1, 1);
}

void Dune::update(float deltaTime)
{
}

void Dune::collide(Actor &actor)
{
	if (getBounds().intersects(actor.getBounds())) {
		actor.slowDown();
	}
}
