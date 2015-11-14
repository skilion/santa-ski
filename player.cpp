#include <cmath>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;
using namespace std;


const float MIN_SPEED = 10;
const float MAX_SPEED = 80;
const float ACCELERATION = 50;

static sf::Texture frame1;

void Player::preload()
{
	frame1.loadFromFile("images/santa.png");
}

Player::Player()
{
	sprite.setTexture(frame1);
	downTime = 0;
}

void Player::goUp()
{
	if (state.down) state.down = false;
	else state.up = true;
}

void Player::goDown()
{
	if (state.up) state.up = false;
	else state.down = true;
}

void Player::goLeft()
{
	if (state.right) state.right = false;
	else state.left = true;
}

void Player::goRight()
{
	if (state.left) state.left = false;
	else state.right = true;
}

void Player::update(float deltaTime)
{
	downTime += deltaTime;
	if (!state.down) {
		downTime = 0;
	}

	Vector2f dir(0, 0);
	if (state.up ^ state.down) {
		if (state.up) dir.y = -1;
		if (state.down) dir.y = 1;
	}
	if (state.left ^ state.right) {
		if (state.left) dir.x = -1;
		if (state.right) dir.x = 1;
	}

	float speed = max(MAX_SPEED, MIN_SPEED + downTime * ACCELERATION);

	sprite.move(normalize(dir) * speed * deltaTime);
}

void Player::collide(Actor &actor)
{
}

void Player::jump()
{
}

void Player::knock()
{
}

void Player::knockHard()
{
}

void Player::slowDown()
{
	downTime = 0;
}
