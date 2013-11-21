
#include "includes.h"





bool Game::launched = false;

sf::Vector2f Game::gravity = sf::Vector2f(-0.01f, 9.82f);

float Game::scale = 10;

sf::Vector2u Game::windowSize(1280, 720);

sf::View Game::view(sf::Vector2f(Game::windowSize.x / 2, Game::windowSize.y / 2), sf::Vector2f(Game::windowSize.x, Game::windowSize.y));





Object::Object() : bzsf::Drawable(), velocity(0,0), mass(0) {
	
}

Object::~Object() {}

void Object::Tick(sf::Time) {}





const sf::FloatRect Player::offsetBoundaryRect = sf::FloatRect(-100, -100, 200, 200);
const float Player::maxFallSpeed = 60.f;

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
					velocity.y -= Game::gravity.y * 10 * Game::scale * mDelta.asSeconds();


		velocity += Game::gravity * Game::scale * mDelta.asSeconds();
		if(velocity.y > (maxFallSpeed * Game::scale)) velocity.y = maxFallSpeed * Game::scale;

		centerPos += velocity * Game::scale * mDelta.asSeconds();

		entity.setPosition(centerPos + offsetPos);
		boundaryRect.setPosition(centerPos);


		// ScreenShake ////////
		ScreenShake::Apply(-airShake); // Remove earlier shake
		
		if(velocity.y > 0) {
			airShake = 0.1f * (velocity.y / maxFallSpeed) * Game::scale;
			ScreenShake::Apply(airShake);
		} else airShake = 0;
		///////////////////////


		// View ////
		Game::view.setCenter(centerPos);

		if(velocity.y > 0) {
			Game::view.setSize(sf::Vector2f(Game::windowSize.x, Game::windowSize.y) * (1.f+(velocity.y/maxFallSpeed)*0.1f));
		}

		////////////

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
				airShake(0),
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