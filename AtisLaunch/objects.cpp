
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <BZeps-SFML-Snippets\SFML_Snips.hpp>

namespace GameState {
	enum State {
		Menu,
		Play,
		Die
	};
}

#include "objects.h"

#include "game_functions.hpp"


Object::Object() : bzsf::Drawable() {
	
}

Object::~Object() {}

void Object::Tick(sf::Time) {}



void Player::Tick(sf::Time mDelta) {


}


Player::Player() {
	sf::Image img; img.create(32, 32, sf::Color(255, 0, 0));
	sf::Texture tex; tex.loadFromImage(img);
	SetTexture(tex);
}