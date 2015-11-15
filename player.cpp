#include <cassert>
#include <cmath>
#include <iostream>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;
using namespace std;


const float MIN_SPEED = 40;
const float MAX_SPEED = 200;
const float ACCELERATION = 50;
const float SMALL_JUMP = 8;
const float BIG_JUMP = 10;
const float JUMP_SPEED = 15;
const float FALL_SPEED = 10;
const float CRASH_STOP_TIME = 2;

static sf::Texture frames[6];

void Player::preload()
{
	frames[0] = loadTexture("images/sprite_1.png");
	frames[1] = loadTexture("images/sprite_2.png");
	frames[2] = loadTexture("images/sprite_3.png");
	frames[3] = loadTexture("images/sprite_4.png");
	frames[4] = loadTexture("images/sprite_5.png");
	frames[5] = loadTexture("images/sprite_6.png");
}

Player::Player()
{
	sprite.setTexture(frames[3]);
	sprite.setOrigin(16, 16);
	speed = 0;
	downTime = 0;
	jumping = false;
	crash = false;
	travelAmount = 0;
}

void Player::goUp()
{
	if (jumping || crash) return;
	if (state.down) state.down = false;
	else {
		if (!state.up) state.up = true;
		else state.left = state.right = false;
	}
}

void Player::goDown()
{
	if (jumping || crash) return;
	if (state.up) state.up = false;
	else {
		if (!state.down) state.down = true;
		else state.left = state.right = false;
	}
}

void Player::goLeft()
{
	if (jumping || crash) return;
	if (state.right) state.right = false;
	else {
		if (!state.left) state.left = true;
		else state.up = state.down = false;
	}
}

void Player::goRight()
{
	if (jumping || crash) return;
	if (state.left) state.left = false;
	else {
		if (!state.right) state.right = true;
		else state.up = state.down = false;
	}
}

void Player::update(float deltaTime)
{
	downTime += deltaTime;
	if (!state.down || crash) {
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

	// set the correct texture
	int id = state.up << 3 | state.down << 2 | state.left << 1 | state.right;
	float xScale = 1;
	switch (id) {
	case 10: sprite.setTexture(frames[2], true); xScale = -1; break;
	case  9: sprite.setTexture(frames[2], true); xScale =  1; break;
	case  8: sprite.setTexture(frames[0], true); xScale =  1; break;
	case  6: sprite.setTexture(frames[4], true); xScale = -1; break;
	case  5: sprite.setTexture(frames[4], true); xScale =  1; break;
	case  4: sprite.setTexture(frames[1], true); xScale =  1; break;
	case  2: sprite.setTexture(frames[3], true); xScale = -1; break;
	case  1: sprite.setTexture(frames[3], true); xScale =  1; break;
	case  0: break;
	default: cerr << "invalid player state"; assert(0);
	}

	float speed = min(MAX_SPEED, MIN_SPEED + downTime * ACCELERATION);

	if (crash) {
		crashTime += deltaTime;
		if (crashTime > CRASH_STOP_TIME) {
			crash = false;
		} else {
			sprite.setTexture(frames[5], true);
			speed = 0;
		}
	}

	Vector2f velocity = normalize(dir) * speed;
	Vector2f movement = velocity * deltaTime;
	travelAmount += movement.y;
	sprite.move(movement);

	this->speed = magnitude(velocity);

	// zoom when jumping
	sprite.setScale(xScale * (1 + height * 0.1), 1 + height * 0.1);
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
	if (!jumping && !crash && speed > MIN_SPEED * 2) {
		crash = true;
		crashTime = 0;
		downTime = 0;
		state.up = state.down = state.left = state.right = false;
	}
}

void Player::knockHard()
{
	// todo
	knock();
}

void Player::slowDown()
{
	if (jumping) return;
	downTime = 0;
}
