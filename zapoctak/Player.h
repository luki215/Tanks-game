#pragma once
#ifndef tanks_components_game_player_header
#define tanks_components_game_player_header
	
#include <string>
#include "TankProperties.h"
namespace TanksGame {
	namespace Components {
		namespace Game {

			struct Player {
			public:
				std::string name;
				TankProperties tank;
				int money;
				bool lost = false;
				Player(std::string name, TankProperties tank_prop, int money) : name{ name }, tank{ tank_prop }, money{ money } {};
			};
		}
	}
}
#endif