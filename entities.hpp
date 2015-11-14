#include <SFML/Graphics.hpp>


class Entity
{
protected:
	sf::Sprite sprite;

public:
	virtual void draw();
	virtual void update(float deltaTime) = 0;
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
