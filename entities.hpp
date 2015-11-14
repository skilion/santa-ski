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
};

class Actor: public Entity
{
public:
	virtual void jump() = 0;
	virtual void knock() = 0;
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
