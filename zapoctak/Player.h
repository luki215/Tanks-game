#pragma once
#ifndef tanks_components_game_player_header
#define tanks_components_game_player_header
	
#include <string>
#include "Tank.h"
namespace TanksGame {
	namespace Components {
		namespace Game {

			class Player {
				std::string name;
				TankProperties tank;
				int money;
			};
		}
	}
}
#endif