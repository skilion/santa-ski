#include <cmath>
#include "util.hpp"
using namespace sf;
using namespace std;

bool collision(CircleShape &a, CircleShape &b)
{
	float r1 = a.getRadius();
	float r2 = b.getRadius();
	float dist = magnitude(a.getPosition() + Vector2f(r1, r1) - b.getPosition() - Vector2f(r2, r2));
	float minDist = r1 + r2;
	return dist < minDist;
}

// https://github.com/SFML/SFML/wiki/Source:-Letterbox-effect-using-a-view
// slightly modified
View getLetterboxView(int desiredWidth, int desiredHeight, int windowWidth, int windowHeight)
{
	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to archieve a letterbox effect.
	// A new view (with a new viewport set) is returned.

	float windowRatio = windowWidth / (float) windowHeight;
	float viewRatio = desiredWidth / (float) desiredHeight;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio) horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.0;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.0;
	}

	View view(FloatRect(0, 0, desiredWidth, desiredHeight));
	view.setViewport(FloatRect(posX, posY, sizeX, sizeY) );
	return view;
}

Vector2f operator*(const Vector2f &a, float b)
{
    Vector2f r(a.x * b, a.y * b);
    return r;
}

Vector2f operator/(const Vector2f &a, float b)
{
    Vector2f r(a.x * b, a.y * b);
    return r;
}

float magnitude(const Vector2f &v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f normalize(const Vector2f &v)
{
	return v / magnitude(v);
}
