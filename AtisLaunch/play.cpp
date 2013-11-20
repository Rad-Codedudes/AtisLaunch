#include <vector>
#include <sstream>


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


void play() {

	sf::Text debugText("Hej!", Resource::defaultFont, 20);
	debugText.setColor(sf::Color(255, 132, 100));


	Resource::background.setRepeated(true);
	sf::Sprite bg(Resource::background, sf::IntRect(0, 0, 100000, 10000000));

	
	objects.push_back(new Player());

	sf::Clock deltaClock;
	sf::Event event;
	while(bzsf::game::currentState == GameState::Play) {

		sf::Time mDelta = deltaClock.restart();

		while(bzsf::game::window->pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed :
					bzsf::game::currentState = GameState::Die;
					break;


				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape) {
						bzsf::game::currentState = GameState::Die;
					}
					break;
			}
		}

		for(Object* o : objects) {
			o->Tick(mDelta);
		}


		bzsf::game::window->clear();

		bzsf::game::window->setView(Game::view);
		bzsf::game::window->draw(bg);

		for(Object* o : objects) {
			o->draw();
		}



		bzsf::game::window->setView(bzsf::game::window->getDefaultView());

		std::stringstream ss; ss << "Vel.x: " << objects[0]->velocity.x << "\nVel.y: " << objects[0]->velocity.y;
		debugText.setString(ss.str());
		bzsf::game::window->draw(debugText);

		bzsf::game::window->display();

	}
}