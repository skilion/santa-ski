#include <vector>
#include "entities.hpp"


class Game
{
	std::vector<Entity*> entities;
	std::vector<Entity*> actors;

public:

	Player player;

	Game();

	void update(float deltaTime);
	void draw();
};
