#include <vector>
#include "entities.hpp"

class Game
{
	std::vector<Entity*> entities;
	std::vector<ActiveEntity*> actors;

	// start true enables the monster
	// end true disable the player
	bool start, end;

	// area where game items are present
	sf::FloatRect gameArea;
	sf::Vector2f areaCenter;

	void collect();
	void updateGameArea();;
	void fillAt(float x, float y);

public:

	Player player;
	Monster *monster;

	Game();

	void update(float deltaTime);
	void draw();

	void begin();
	void finish();
};
