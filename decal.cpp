#include <cstdlib>
#include <iostream>
#include "entities.hpp"
#include "util.hpp"
using namespace sf;
using namespace std;

static Texture blood[2];
static Texture fall[2];
static Texture tracks[2];
static Texture warningSign[2];
static Texture welcomeSign;

void Decal::preload()
{
	blood[0] = loadTexture("images/blood1.png");
	blood[1] = loadTexture("images/blood2.png");
	fall[0] = loadTexture("images/fall1.png");
	fall[1] = loadTexture("images/fall2.png");
	tracks[0] = loadTexture("images/tracks1.png");
	tracks[1] = loadTexture("images/tracks2.png");
	warningSign[0] = loadTexture("images/warning_sign1.png");
	warningSign[1] = loadTexture("images/warning_sign2.png");
	welcomeSign = loadTexture("images/welcome_sign.png");
}

Decal::Decal(Decal::Type type)
{
	int n = rand();
	switch (type) {
	case BLOOD:
		sprite.setTexture(blood[n % 1]);
		break;
	case FALL:
		sprite.setTexture(fall[n % 1]);
		break;
	case TRACKS:
		sprite.setTexture(tracks[n % 1]);
		break;
	case WARNING_SIGN1:
		sprite.setTexture(warningSign[0]);
		break;
	case WARNING_SIGN2:
		sprite.setTexture(warningSign[1]);
		break;
	case WELCOME_SIGN:
		sprite.setTexture(welcomeSign);
		break;
	default:
		cerr << "invalid decal" << endl;
		throw 1;
	}
}

void Decal::update(float deltaTime)
{
}
