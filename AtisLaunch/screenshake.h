
// Klasse til h�ndtering af rystning af sk�rmen ("Screen Shake")

class ScreenShake {
	static float shake;
	static std::vector<std::pair<sf::Time, float>> decay;
	static sf::Clock clock;

public:
	static void Reset();

	static void Apply(float v);
	static void Apply(float v, float decayps);
	static void Apply(float v, sf::Time decayTime);

	static void SetView(sf::View&);
};