

class Object : public bzsf::Drawable {

public:
	virtual void Tick(sf::Time);

	Object();
	virtual ~Object();
};



class Player : public Object {

public:
	void Tick(sf::Time);

	Player();
};