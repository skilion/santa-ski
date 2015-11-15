#pragma once
#include <SFML/Graphics.hpp>

class Actor;
class Game;

class Entity
{
protected:
	sf::Sprite sprite;

public:
	virtual void update(float deltaTime) = 0;
	virtual void collide(Actor &actor) = 0;

	void draw();
	void setPosition(float x, float y);
	const sf::Vector2f &getPosition();
	sf::FloatRect getBounds();
};

class Actor: public Entity
{
public:
	virtual void jump() = 0;
	virtual void bigJump() = 0;
	virtual void knock() = 0;
	virtual void knockHard() = 0;
	virtual void slowDown() = 0;
};

class Player: public Actor
{
	struct PlayerState {
		bool up: 1;
		bool down: 1;
		bool left: 1;
		bool right: 1;
		unsigned int padding: 28;

		PlayerState(): up(0), down(0), left(0), right(0) {}
	} state;

	// time passed going downHill
	float downTime;

	// true if jumping
	bool jumping;
	// true if the jump is big (= more height)
	bool isBigJump;
	// true if it's the descending part of the jump
	bool fall;
	// height of the jump
	float height;

	// true if the player has crashed
	bool crash;
	// time spent after crash
	float crashTime;

public:
	float speed;

	// distance traveled in the vertical direction
	float travelAmount;

	static void preload();

	Player();

	void goUp();
	void goDown();
	void goLeft();
	void goRight();

	void update(float deltaTime);
	void collide(Actor &actor);
	void jump();
	void bigJump();
	void knock();
	void knockHard();
	void slowDown();
};

class Decal: public Entity
{
public:

	enum Type {
		BLOOD,
		FALL,
		TRACKS,
		WARNING_SIGN1,
		WARNING_SIGN2,
		WELCOME_SIGN,
		WELCOME_SIGN2,
	};

	static void preload();

	Decal(Type type);

	void update(float deltaTime);
	void collide(Actor &actor);
};


class ActiveEntity: public Entity
{
public:
};

class Tree: public Entity
{
public:
	static void preload();

	Tree();

	void update(float deltaTime);
	void collide(Actor &actor);
};

class Rock: public Entity
{
public:
	static void preload();

	Rock();

	void update(float deltaTime);
	void collide(Actor &actor);
};

class Dune: public Entity
{
public:
	static void preload();

	Dune();

	void update(float deltaTime);
	void collide(Actor &actor);
};

class Jump: public Entity
{
public:
	static void preload();

	Jump();

	void update(float deltaTime);
	void collide(Actor &actor);
};

class Monster: public Actor
{
	enum State {
		CHASING,
		EATING,
		CELEBRATING
	} state;

	Game *game;

	// for animations
	float time;
	float eatingTime;

public:
	static void preload();

	Monster(Game *game);

	void update(float deltaTime);
	void collide(Actor &actor);
	void jump();
	void bigJump();
	void knock();
	void knockHard();
	void slowDown();
};
