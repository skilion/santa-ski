#include <vector>
#include "entities.hpp"


class Game
{
	std::vector<Entity*> entities;

public:

	Player player;

	Game();

	void update(float deltaTime);
	void draw();
};
