#include <cassert>
#include <iostream>
#include "entities.hpp"
#include "game.hpp"
#include "util.hpp"
using namespace sf;
using namespace std;


const float SPEED = 150;
const float EAT_FRAME_DURATION = 2;

static sf::Texture frames[5];

void Monster::preload()
{
	frames[0] = loadTexture("images/monster1.png");
	frames[1] = loadTexture("images/monster2.png");
	frames[2] = loadTexture("images/monster3.png");
	frames[3] = loadTexture("images/monster4.png");
	frames[4] = loadTexture("images/monster5.png");
}

Monster::Monster(Game *game)
{
	this->game = game;
	assert(game);
	sprite.setTexture(frames[0]);
	state = CHASING;
	time = 0;
	eatingTime = -1;
}

void Monster::update(float deltaTime)
{
	time += deltaTime;


	switch (state) {
	case CHASING:
		sprite.setTexture(frames[(int) (time * 2) % 2], true);
		// move
		{
			Vector2f dir = game->player.getPosition() - getPosition();
			Vector2f velocity = normalize(dir) * SPEED;
			sprite.move(velocity * deltaTime);
		}
		break;
	case EATING:
		sprite.setTexture(frames[2], true);
		break;
	case CELEBRATING:
		sprite.setTexture(frames[3 + (int) (time * 2) % 2], true);
		break;
	}

	if (eatingTime > 0) {
		float diff = time - eatingTime;
		if (diff > EAT_FRAME_DURATION) {
			state = CELEBRATING;
		}
	}
}

void Monster::collide(Actor &actor)
{
	if ((state == CHASING) && getBounds().intersects(actor.getBounds())) {
		cerr << "EATEN" << endl;
		state = EATING;
		eatingTime = time;
		game->finish();
	}
}

void Monster::jump()
{
	// nothing to do
}

void Monster::bigJump()
{
	// nothing to do
}

void Monster::knock()
{
	// nothing to do
}

void Monster::knockHard()
{
	// nothing to do
}

void Monster::slowDown()
{
	// nothing to do
}
