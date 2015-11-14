#include <SFML/Graphics.hpp>

bool collision(sf::CircleShape &a, sf::CircleShape &b);
sf::View getLetterboxView(int desiredWidth, int desiredHeight, int windowWidth, int windowHeight);

sf::Vector2f operator*(const sf::Vector2f &a, float b);
sf::Vector2f operator/(const sf::Vector2f &a, float b);
float magnitude(const sf::Vector2f &v);
sf::Vector2f normalize(const sf::Vector2f &v);
