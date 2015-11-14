#include <cstdlib>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;


static Texture trees[5];

void Tree::preload()
{
	trees[0] = loadTexture("images/tree1.png");
	trees[1] = loadTexture("images/tree2.png");
	trees[2] = loadTexture("images/tree3.png");
	trees[3] = loadTexture("images/tree4.png");
	trees[4] = loadTexture("images/christmas_tree.png");
}

Tree::Tree()
{
	int n = rand();
	sprite.setTexture(trees[n % 4], true);
	// christmas tree
	if (n % 100 == 99) sprite.setTexture(trees[4], true);
}

void Tree::update(float deltaTime)
{
}

void Tree::collide(Actor &actor)
{
	if (getBounds().intersects(actor.getBounds())) {
		actor.knock();
	}
}
