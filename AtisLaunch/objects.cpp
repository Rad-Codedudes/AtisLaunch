
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





bool Game::launched = false;

sf::Vector2f Game::gravity = sf::Vector2f(0, 9.82f);

float Game::scale = 10;

sf::View Game::view(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));




Object::Object() : bzsf::Drawable(), velocity(0,0), mass(0) {
	
}

Object::~Object() {}

void Object::Tick(sf::Time) {}





const sf::FloatRect Player::offsetBoundaryRect = sf::FloatRect(-100, -100, 200, 200);


void Player::Tick(sf::Time mDelta) {
	
	if(!Game::launched) {

		entity.setPosition(centerPos);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Game::launched = true;
		}

	} else {

		//// Offset //////////////////

		sf::Vector2f offset(0, 0);


		if(offsetPos.y < 0) {

			offset.y = 1000 * ((offsetPos.y - offsetBoundaryRect.top) / offsetBoundaryRect.height / 2);

		} else if(offsetPos.y > 0) {

			offset.y = -1000 * (offsetPos.y / (offsetBoundaryRect.height / 2));

		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			offset.y = -1000 * ((offsetPos.y - offsetBoundaryRect.top) / offsetBoundaryRect.height); 
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			offset.y = 1000 * ((offsetBoundaryRect.height - (offsetPos.y - offsetBoundaryRect.top)) / offsetBoundaryRect.height);
		}


		offsetPos += offset * mDelta.asSeconds();





		




		//////////////////////////


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					velocity.y -= 100 * mDelta.asSeconds();


		velocity += Game::gravity * Game::scale * mDelta.asSeconds();
		velocity.y = 0;
		velocity.x = 0;

		centerPos += velocity * Game::scale * mDelta.asSeconds();

		entity.setPosition(centerPos + offsetPos);

		Game::view.setCenter(centerPos);
	}
}


Player::Player() : centerPos(100, 600), 
				offsetPos(0, 0) {
	sf::Image img; img.create(32, 32, sf::Color(255, 0, 0));
	sf::Texture tex; tex.loadFromImage(img);
	SetTexture(tex);
	entity.setOrigin(entity.getLocalBounds().width / 2,
					 entity.getLocalBounds().height / 2);

	velocity = sf::Vector2f(20, -20);
	mass = 80;
}