
class Game {
public:
	static bool launched;

	static sf::Vector2f gravity;

	static float scale;

	static sf::View view;
};



class Object : public bzsf::Drawable {
public:
	sf::Vector2f velocity;

	float mass;

	virtual void Tick(sf::Time);

	Object();
	virtual ~Object();
};



class Player : public Object {
	sf::Vector2f centerPos;
	sf::Vector2f offsetPos;

	static const sf::FloatRect offsetBoundaryRect;

public:
	void Tick(sf::Time);

	Player();
};