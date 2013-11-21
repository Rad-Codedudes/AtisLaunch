#include <vector>
#include <sstream>
#include <time.h>


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

#include "res.h"
#include "screenshake.h"

#include "objects.h"

#include "game_functions.hpp"