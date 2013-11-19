#include <vector>


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


void play() {

	std::vector<Object*> objects;
	objects.push_back(new Player());

	sf::View view(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));

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

		bzsf::game::window->setView(view);


		for(Object* o : objects) {
			o->draw();
		}


		bzsf::game::window->display();

	}
}