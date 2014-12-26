#include "includes.h"


namespace sf {
	float operator /(Time left, Time right) {
		return left.asSeconds() / right.asSeconds();
	}
}



int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL)); // Sæt et seed til tilfældighedsgeneratoren

	LoadResources();


	bzsflegacy::game::addFunc(GameState::Menu, menu);
	bzsflegacy::game::addFunc(GameState::Play, play);
	bzsflegacy::game::addFunc(GameState::Die, bzsflegacy::game_die);

	bzsflegacy::game::currentState = GameState::Play;

	// Lav vindue
	bzsflegacy::game::window = new sf::RenderWindow(sf::VideoMode(Game::windowSize.x, 
															Game::windowSize.y, 
															32), 
											"AtisLaunch", 
											sf::Style::Close);

	bzsflegacy::game::window->setVerticalSyncEnabled(true);

	return bzsflegacy::game::runGame(); // KØR SPILLET
}


void menu() {
	sf::Clock clock;

	while(clock.getElapsedTime() < sf::seconds(5)) {
		bzsflegacy::game::window->clear(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		bzsflegacy::game::window->display();
	}

	bzsflegacy::game::currentState = GameState::Die;


}