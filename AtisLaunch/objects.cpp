
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

#include "res.h"

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


sf::Vector2f Player::CalculateOffset() {
	sf::Vector2f offset(0, 0);


	/// x-axis
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		offset.x = -1000 * ((offsetPos.x - offsetBoundaryRect.left) / offsetBoundaryRect.width);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		offset.x = 1000 * ((offsetBoundaryRect.width - (offsetPos.x - offsetBoundaryRect.left)) / offsetBoundaryRect.width);
	} else {
		if(offsetPos.x < 0) {

			offset.x = 1000 * (((offsetBoundaryRect.width / 2) - (offsetPos.x - offsetBoundaryRect.left)) / (offsetBoundaryRect.width / 2));

		} else if(offsetPos.x > 0) {

			offset.x = -1000 * (offsetPos.x / (offsetBoundaryRect.width / 2));

		}
	}



	/// y-axis
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		offset.y = -1000 * ((offsetPos.y - offsetBoundaryRect.top) / offsetBoundaryRect.height);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		offset.y = 1000 * ((offsetBoundaryRect.height - (offsetPos.y - offsetBoundaryRect.top)) / offsetBoundaryRect.height);
	} else {
		if(offsetPos.y < 0) {

			offset.y = 1000 * (((offsetBoundaryRect.height / 2) - (offsetPos.y - offsetBoundaryRect.top)) / (offsetBoundaryRect.height / 2));

		} else if(offsetPos.y > 0) {

			offset.y = -1000 * (offsetPos.y / (offsetBoundaryRect.height / 2));

		}
	}

	return offset;
}


void Player::Tick(sf::Time mDelta) {
	
	if(!Game::launched) {

		entity.setPosition(centerPos);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Game::launched = true;
		}

	} else {

		//// Offset //////////////////
		offsetPos += CalculateOffset() * mDelta.asSeconds();
		//////////////////////////


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					velocity.y -= 1000 * mDelta.asSeconds();


		velocity += Game::gravity * Game::scale * mDelta.asSeconds();

		centerPos += velocity * Game::scale * mDelta.asSeconds();

		entity.setPosition(centerPos + offsetPos);
		boundaryRect.setPosition(centerPos);

		Game::view.setCenter(centerPos);



		// Update posText
		std::stringstream ss; ss << centerPos.x << std::endl << centerPos.y;
		posText.setString(ss.str());
		posText.setPosition(centerPos + offsetPos - sf::Vector2f(32, 64));
	}
}

void Player::draw() {
	bzsf::game::window->draw(boundaryRect);

	bzsf::game::window->draw(posText);

	bzsf::game::window->draw(entity);
}


Player::Player() : centerPos(100, 600), 
				offsetPos(0, 0),
				boundaryRect(sf::Vector2f(offsetBoundaryRect.width, offsetBoundaryRect.height)),
				posText("", Resource::defaultFont, 12) {
	
	sf::Image img; img.create(32, 32, sf::Color(255, 0, 0));
	sf::Texture tex; tex.loadFromImage(img);
	SetTexture(tex);
	entity.setOrigin(entity.getLocalBounds().width / 2,
					 entity.getLocalBounds().height / 2);

	boundaryRect.setOrigin(offsetBoundaryRect.width / 2,
						   offsetBoundaryRect.height / 2);
	boundaryRect.setOutlineThickness(2.f);
	boundaryRect.setOutlineColor(sf::Color());
	boundaryRect.setFillColor(sf::Color(240, 240, 255, 128));

	posText.setColor(sf::Color());

	velocity = sf::Vector2f(100, -100);
	mass = 80;
}