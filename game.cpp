#include "entities.hpp"
#include "game.hpp"
//using namespace sf;
using namespace std;

Game::Game()
{
	entities.reserve(16);
	actors.reserve(16);

	Entity *welcomeSign = new Decal(Decal::WELCOME_SIGN);
	welcomeSign->setPosition(100, 100);
	entities.push_back(welcomeSign);

	Entity *dune = new Dune();
	dune->setPosition(200, 400);
	entities.push_back(dune);

	Entity *jump = new Jump();
	jump->setPosition(300, 300);
	entities.push_back(jump);
}

void Game::update(float deltaTime)
{
	player.update(deltaTime);
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]) entities[i]->update(deltaTime);
		entities[i]->collide(player);
	}
}

void Game::draw()
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->draw();
	}
	player.draw();
}
