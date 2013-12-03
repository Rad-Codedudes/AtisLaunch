#include "includes.h"


namespace sf {
	float operator /(Time left, Time right) {
		return left.asSeconds() / right.asSeconds();
	}
}



int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));

	LoadResources();


	bzsf::game::addFunc(GameState::Menu, menu);
	bzsf::game::addFunc(GameState::Play, play);
	bzsf::game::addFunc(GameState::Die, bzsf::game_die);

	bzsf::game::currentState = GameState::Play;

	bzsf::game::window = new sf::RenderWindow(sf::VideoMode(Game::windowSize.x, 
															Game::windowSize.y, 
															32), 
											"AtisLaunch", 
											sf::Style::Close);

	bzsf::game::window->setVerticalSyncEnabled(true);

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