#include <cmath>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;
using namespace std;


const float MIN_SPEED = 2;
const float MAX_SPEED = 80;
const float ACCELERATION = 50;
const float SMALL_JUMP = 8;
const float BIG_JUMP = 10;
const float JUMP_SPEED = 15;
const float FALL_SPEED = 10;

static sf::Texture frame1;

void Player::preload()
{
	frame1.loadFromFile("images/santa.png");
}

Player::Player()
{
	sprite.setTexture(frame1);
	downTime = 0;
	jumping = false;
}

void Player::goUp()
{
	if (jumping) return;
	if (state.down) state.down = false;
	else state.up = true;
}

void Player::goDown()
{
	if (jumping) return;
	if (state.up) state.up = false;
	else state.down = true;
}

void Player::goLeft()
{
	if (jumping) return;
	if (state.right) state.right = false;
	else state.left = true;
}

void Player::goRight()
{
	if (jumping) return;
	if (state.left) state.left = false;
	else state.right = true;
}

void Player::update(float deltaTime)
{
	downTime += deltaTime;
	if (!state.down) {
		// stopped going downhill
		downTime = 0;
	}

	if (jumping) {
		if (!fall) {
			height += deltaTime * JUMP_SPEED;
			if (!isBigJump) {
				if (height >= SMALL_JUMP) {
					fall = true;
				}
			} else {
				if (height >= BIG_JUMP) {
					fall = true;
				}
			}
		} else {
			height -= deltaTime * FALL_SPEED;
			if (height <= 0) {
				height = 0;
				jumping = false;
			}
		}
	}

	// generate direction vector
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
	sprite.setScale(1 + height * 0.1, 1 + height * 0.1);
}

void Player::collide(Actor &actor)
{
	// not used
}

void Player::jump()
{
	if (!jumping && state.down) {
		jumping = true;
		isBigJump = false;
		fall = false;
		height = 0;
	}
}

void Player::bigJump()
{
	jump();
	isBigJump = true;
}

void Player::knock()
{
}

void Player::knockHard()
{
}

void Player::slowDown()
{
	if (jumping) return;
	downTime = 0;
}
