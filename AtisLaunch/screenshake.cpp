#include "includes.h"

float ScreenShake::shake = 0;
std::vector<std::pair<sf::Time, float>> ScreenShake::decay = std::vector<std::pair<sf::Time, float>>();
sf::Clock ScreenShake::clock = sf::Clock();


void ScreenShake::Reset() {
	shake = 0;
	decay.erase(decay.begin(), decay.end()); // Tøm vektoren
	clock.restart();
}


void ScreenShake::Apply(float v, sf::Time decayTime) {
	shake += v;
	decay.push_back(std::make_pair(decayTime, v * (sf::seconds(1) / decayTime)));
}

void ScreenShake::Apply(float v, float decayps) {
	Apply(v, sf::seconds(v / decayps));
}

void ScreenShake::Apply(float v) { shake += v; }


void ScreenShake::SetView(sf::View& view) {
	sf::Time elapsed = clock.restart();

	// Fjern fra vektoren hvis tiden er gået
	decay.erase(std::remove_if(decay.begin(), decay.end(), [](const std::pair<sf::Time, float>& p) {return p.first == sf::Time::Zero; }),
				decay.end());


	for(std::pair<sf::Time, float>& p : decay) {
		if(elapsed < p.first) {
			shake -= p.second * elapsed.asSeconds();
			p.first -= elapsed;
		} else {
			shake -= ((p.first / elapsed) * (elapsed / sf::seconds(1))) * p.second;
			p.first = sf::Time::Zero;
		}
	}

	if(shake < 0) { /*std::cout << "Shake went under 0 lol" << std::endl;*/ shake = 0; }


	
	sf::Vector2f pos = view.getCenter();
	sf::Vector2f sPos(pos);
	sf::Int32	r = sf::Int32(shake * 10 * 2); sPos.x += shake - (r != 0 ? (float(rand() % r) / 10.f) : 0);
				r = sf::Int32(shake * 10 * 2); sPos.y += shake - (r != 0 ? (float(rand() % r) / 10.f) : 0);
	

	view.setCenter(sPos);


	float rot = view.getRotation();
	float sRot = rot;
				r = sf::Int32(shake * 10.f * 2); sRot += (-shake + (r != 0 ? (float(rand() % r) / 10.f) : 0))/10.f;

	view.setRotation(sRot);


	bzsflegacy::game::window->setView(view);

	view.setCenter(pos);
	view.setRotation(rot);
}