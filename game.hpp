#include <vector>
#include "entities.hpp"

class Game
{
	std::vector<Entity*> entities;
	std::vector<ActiveEntity*> actors;

	// area where game items are present
	sf::FloatRect gameArea;
	sf::Vector2f areaCenter;

	void collect();
	void updateGameArea();;
	void fillAt(float x, float y);

public:

	Player player;

	Game();

	void update(float deltaTime);
	void draw();

};
