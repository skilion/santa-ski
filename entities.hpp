#pragma once
#include <SFML/Graphics.hpp>


class Entity
{
protected:
	sf::Sprite sprite;

public:
	virtual void update(float deltaTime) = 0;

	void draw();
	void setPosition(float x, float y);
	sf::FloatRect getBounds();
};

class Actor: public Entity
{
public:
	virtual void jump() = 0;
	virtual void knock() = 0;
	virtual void knockHard() = 0;
	virtual void slowDown() = 0;
};

class Player: public Entity
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

public:

	static void preload();

	Player();
	void update(float deltaTime);

	void goUp();
	void goDown();
	void goLeft();
	void goRight();
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
		WELCOME_SIGN
	};

	static void preload();

	Decal(Type type);

	void update(float deltaTime);
};


class TriggerEntity: public Entity
{
public:
	virtual void collide(Actor &actor) = 0;
};

class Tree: public TriggerEntity
{
public:
	static void preload();

	Tree();

	void collide(Actor &actor);
};

class Rock: public TriggerEntity
{
public:
	static void preload();

	Rock();

	void collide(Actor &actor);
};

class Dune: public TriggerEntity
{
public:
	static void preload();

	Dune();

	void collide(Actor &actor);
};
