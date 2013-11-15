
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

#include "game_functions.hpp"

int main(int argc, char* argv[]) {

	bzsf::game::addFunc(GameState::Menu, menu);
	bzsf::game::addFunc(GameState::Die, bzsf::game_die);

	bzsf::game::currentState = GameState::Menu;

	bzsf::game::window = new sf::RenderWindow(sf::VideoMode(1280, 720, 32), "AtisLaunch", sf::Style::Close);

	return bzsf::game::runGame();
}