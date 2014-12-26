#include <vector>
#include <sstream>
#include <time.h>
#include <math.h>

// Grafik funktioner
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

// Extension
#include <bzsf\SFML_Snips.hpp>


namespace GameState {
	enum State {
		Menu,
		Play,
		Die
	};
}

#include "res.h" // resources

#include "screenshake.h"

#include "upgrades.h"
#include "objects.h"

#include "game_functions.hpp"