
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

int main(int argc, char* argv[]) {

	LoadResources();


	bzsf::game::addFunc(GameState::Menu, menu);
	bzsf::game::addFunc(GameState::Play, play);
	bzsf::game::addFunc(GameState::Die, bzsf::game_die);

	bzsf::game::currentState = GameState::Play;

	bzsf::game::window = new sf::RenderWindow(sf::VideoMode(1280, 720, 32), "AtisLaunch", sf::Style::Close);

	return bzsf::game::runGame();
}


void menu() {
	sf::Clock clock;

	while(clock.getElapsedTime() < sf::seconds(5)) {
		bzsf::game::window->clear(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		bzsf::game::window->display();
	}

	bzsf::game::currentState = GameState::Die;


}