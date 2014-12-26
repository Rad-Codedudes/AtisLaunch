#include "includes.h"


void play() {

	sf::Text debugText("Hej!", Resource::defaultFont, 20);
	debugText.setColor(sf::Color(255, 132, 100));

	sf::Text fpsText("", Resource::fpsFont, 16);
	fpsText.setColor(sf::Color());
	fpsText.setPosition(Game::windowSize.x - 100, Game::windowSize.y - 20);


	Resource::background.setRepeated(true);
	sf::Sprite bg(Resource::background, sf::IntRect(0, 0, 100000, 10000000));

	Player* player = new Player();
	objects.push_back(player);

	// Distance inden næste fjende skal spawnes
	double nextObject = 100;

	sf::Clock deltaClock;
	sf::Clock fpsClock;
	sf::Event event;
	while(bzsflegacy::game::currentState == GameState::Play) {

		sf::Time mDelta = deltaClock.restart(); // Udregn tid der er gået siden starten af sidste frame
		// Dette er vigtigt, da tiden mellem hver frame kan variere, og vi derfor bliver nødt til at
		// skalere alle bevægelser med denne værdi

		


		while(bzsflegacy::game::window->pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed :
					bzsflegacy::game::currentState = GameState::Die;
					break;


				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape) {
						bzsflegacy::game::currentState = GameState::Die;
					} else if(event.key.code == sf::Keyboard::R) { // Genstart spillet
						Game::launched = false;
						for(Object* o : objects) {
							delete o;
						}
						nextObject = 100;

						objects.erase(objects.begin(), objects.end());

						player = new Player();
						objects.push_back(player);


						Game::view.setCenter(sf::Vector2f(Game::windowSize.x/2, Game::windowSize.y/2));
						Game::view.setSize(sf::Vector2f(Game::windowSize.x, Game::windowSize.y));
						ScreenShake::Reset();
					}
					break;

				case sf::Event::MouseButtonReleased:
					if(event.mouseButton.button == sf::Mouse::Left && !Game::launched)
						player->Launch();
					break;
			}
		}

		for(Object* o : objects) {
			o->Tick(mDelta); // Tick alle objekter
		}

		if (player->getPosition().x >= nextObject) {
			//Spawn object

			do {
				sf::Vector2f pos(1000 + rand() % 300, -600 + rand() % 1200);

				pos.y += player->getPosition().y + (player->velocity.y / player->velocity.x) * pos.x;
				pos.x += player->getPosition().x;

				objects.push_back(new Enemy(pos, sf::Vector2f(0,0)));
					

			} while (rand() % 3 == 0);


			nextObject += 20 + (rand() % 200);

		}

		// Fjern alt fra vinduet
		bzsflegacy::game::window->clear();

		ScreenShake::SetView(Game::view);
		bzsflegacy::game::window->draw(bg); // Tegn baggrunden

		for(Object* o : objects) {
			bzsflegacy::game::window->draw(*o); // Tegn alle objekter
		}



		bzsflegacy::game::window->setView(bzsflegacy::game::window->getDefaultView());

		std::stringstream ss; 
		ss << "Vel.x: " << player->velocity.x
			<< "\nVel.y: " << player->velocity.y;
		debugText.setString(ss.str());
		bzsflegacy::game::window->draw(debugText);


		// Udregn FPS hvis der er gået mere end 100ms siden det blev gjort sidst
		if(fpsClock.getElapsedTime() > sf::seconds(0.1)) {
			char cfps[8]; _itoa(sf::seconds(1) / mDelta, cfps, 10);
			fpsText.setString(cfps);
			fpsClock.restart();
		}
		bzsflegacy::game::window->draw(fpsText);

		bzsflegacy::game::window->display();

	}
}