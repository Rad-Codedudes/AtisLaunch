
void menu() {
	sf::Clock clock;

	while(clock.getElapsedTime() < sf::seconds(5)) {
		bzsf::game::window->clear(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		bzsf::game::window->display();
	}

	bzsf::game::currentState = GameState::Die;


}