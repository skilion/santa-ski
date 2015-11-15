#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entities.hpp"
#include "game.hpp"
#include "global.hpp"
#include "util.hpp"
using namespace sf;
using namespace std;


int main()
{
	window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "Santa Ski");
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(60);
	srand(time(NULL));

	// load resources
	Decal::preload();
	Player::preload();
	Tree::preload();
	Rock::preload();
	Dune::preload();
	Jump::preload();
	Monster::preload();
	bool result = defaultFont.loadFromFile("fonts/Munro.ttf");
	assert(result);

	Game game;

	Clock clock;
	while (window->isOpen()) {
		// event loop
		Event event;
		while (window->pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window->close();
				break;
			case Event::Resized:
				// keep a nice viewport
				{
					View view = getLetterboxView(WIDTH, HEIGHT, event.size.width, event.size.height);
					window->setView(view);
				}
				break;
			case Event::KeyPressed:
				switch (event.key.code) {
				case Keyboard::Up: game.player.goUp(); break;
				case Keyboard::Down: game.player.goDown(); break;
				case Keyboard::Left: game.player.goLeft(); break;
				case Keyboard::Right: game.player.goRight(); break;
				}
				break;
			}
		}

		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		game.update(deltaTime);

		// center on the player
		View view = window->getView();
		view.setCenter(game.player.getPosition());
		window->setView(view);

		window->clear(snowColor);
		game.draw();
		window->display();
    }

	delete window;
	return 0;
}
