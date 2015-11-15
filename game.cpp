#include <cmath>
#include <iostream>
#include <sstream>
#include "entities.hpp"
#include "game.hpp"
#include "global.hpp"
using namespace sf;
using namespace std;

const int AREA_SIZE = WIDTH * 2;
const int AREA_DIFF = WIDTH * 1;
const float FILL_STEP = 32;
const float PART1_LENGTH = 500;
const float PART2_LENGTH = 5000;
const float PART3_LENGTH = 10000;

Game::Game()
{
	entities.reserve(16);
	actors.reserve(16);

	Entity *welcomeSign = new Decal(Decal::WELCOME_SIGN);
	welcomeSign->setPosition(-200, 100);
	entities.push_back(welcomeSign);

	Entity *welcomeSign2 = new Decal(Decal::WELCOME_SIGN2);
	welcomeSign2->setPosition(200, 100);
	entities.push_back(welcomeSign2);

	monster = new Monster(this);

	start = end = false;
	updateGameArea();
}

void Game::update(float deltaTime)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]) entities[i]->update(deltaTime);
		entities[i]->collide(player);
	}

	// special entities
	if (!end) player.update(deltaTime);
	if (start) {
		monster->collide(player);
		monster->update(deltaTime);
	}

	// test if it time to update the game area
	Vector2f playerPos = player.getPosition();
	if ((abs(playerPos.x - areaCenter.x) > AREA_DIFF) || (abs(playerPos.y - areaCenter.y) > AREA_DIFF)) {
		updateGameArea();
	}


	// monster activation
	if (!start && (player.travelAmount > PART2_LENGTH || player.travelAmount < -200)) {
		begin();
	}
}

void Game::draw()
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->draw();
	}

	// special entities
	if (!end) player.draw();
	if (start) monster->draw();

	const View &view = window->getView();
	float originX = view.getCenter().x - WIDTH / 2;
	float originY = view.getCenter().y - HEIGHT / 2;

	Text text;
	text.setFont(defaultFont);
	text.setCharacterSize(32);
	text.setColor(Color::Black);
	ostringstream textStream;

	textStream.str(string());
	textStream << "Speed: ";
	textStream << (int) player.speed / 10;
	text.setString(textStream.str());
	text.setPosition(originX, originY);
	window->draw(text);

	textStream.str(string());
	textStream << "Distance: ";
	textStream << (int) player.travelAmount;
	text.setString(textStream.str());
	text.setPosition(originX, originY + 40);
	window->draw(text);
}

// remove any entities outside the game area
void Game::collect()
{
	for (int i = entities.size() - 1; i > 0; i--) {
		if (!gameArea.intersects(entities[i]->getBounds())) {
			delete entities[i];
			entities.erase(entities.begin() + i);
		}
	}
}

void Game::updateGameArea()
{
	cerr << "updateGameArea()" << endl;

	Vector2f playerPos = player.getPosition();
	FloatRect newArea(playerPos.x - AREA_SIZE, playerPos.y - AREA_SIZE, AREA_SIZE * 2, AREA_SIZE * 2);

	for (float x = 0; x < newArea.width; x += FILL_STEP) {
		float xx = newArea.left + x;
		for (float y = 0; y < newArea.height; y += FILL_STEP) {
			float yy = newArea.top + y;
			if (!gameArea.contains(xx, yy)) {
				fillAt(xx, yy);
			}
		}
	}

	gameArea = newArea;
	areaCenter = playerPos;
	collect();
}

void Game::fillAt(float x, float y)
{
	int invDensity;
	// difficulty
	if (y < PART1_LENGTH) {
		return;
	} else if (y < PART2_LENGTH) {
		invDensity = 40;
	} else if (y < PART3_LENGTH) {
		invDensity = 20;
	} else {
		invDensity = 10;
	}
	if (rand() % invDensity == 1) {
		Entity *entity;
		switch (rand() % 9) {
		case 0:
			{
				Decal::Type type;
				int n = rand() % 100;
				if (n < 10) type = Decal::BLOOD;
				else if (n < 50)  type = Decal::FALL;
				else if (n < 80)  type = Decal::TRACKS;
				else if (n < 90)  type = Decal::WARNING_SIGN1;
				else if (n < 100)  type = Decal::WARNING_SIGN2;
				// skip signs
				if (y < PART2_LENGTH) {
					if (type >= Decal::WARNING_SIGN1) type = Decal::TRACKS;
				}
				// skip blood
				if (y < PART3_LENGTH) {
					if (type == Decal::BLOOD) type = Decal::FALL;
				}
				entity = new Decal(type);
			}
			break;
		case 1:
		case 2:
		case 3:
			entity = new Tree();
			break;
		case 4:
		case 5:
			entity = new Rock();
			break;
		case 6:
			entity = new Jump();
			break;
		case 7:
		case 8:
			entity = new Dune();
		}
		entity->setPosition(x + rand() % 10, y + rand() % 10);
		entities.push_back(entity);
	}
}

void Game::begin()
{
	Vector2f pos = player.getPosition();
	monster->setPosition(pos.x - 500, pos.y - 500);
	start = true;
}

void Game::finish()
{
	end = true;
}
