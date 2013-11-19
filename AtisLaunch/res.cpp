#include <vector>

#include <SFML\Graphics.hpp>

#include "res.h"

class Object;
std::vector<Object*> objects = std::vector<Object*>();


sf::Font Resource::defaultFont = sf::Font();
sf::Texture Resource::background = sf::Texture();

void LoadResources() {

	Resource::defaultFont.loadFromFile("res/calibri.ttf");
	Resource::background.loadFromFile("res/bg.png");
}