#pragma once
#pragma once
#ifndef tanks_components_game_tank_properties_header
#define tanks_components_game_tank_properties_header

#include "BasicStructures.h"
#include "TanksAppManager.h"
#include <map>
#include <random>
namespace TanksGame {
	namespace Components {
		namespace Game {
			struct TankProperties {
				using s_uint = uint_least16_t;
				uint_least8_t player;
				s_uint max_health;
				s_uint health;
				s_uint max_fuel;
				s_uint fuel;
				s_uint max_speed;
				s_uint max_strength;
				s_uint current_strength;
				BasicStructres::Color color;
				int init_x_position;
				std::map<std::string, std::pair<int, int>> fireballs;
				std::string current_fireball;
				int current_fireball_count;
			public:
				TankProperties(uint_least8_t player, s_uint x_position) :player{ player }, max_health{ 100 }, health{ 100 }, max_fuel{ 100 }, fuel{ 100 }, max_speed{ 2 }, max_strength{ 30 }, current_strength{ 15 }, color{ BasicStructres::Color{ 0x000000 } }, init_x_position{ x_position }, fireballs{ std::map<std::string, std::pair<int,int>>{} } {
					fireballs.emplace("small-missile", std::pair<int, int>{50, 100});
					fireballs.emplace("large-missile", std::pair<int, int>{0, 500});
					fireballs.emplace("atom-bomb", std::pair<int, int>{0, 5000});
					fireballs.emplace("nitrogen-bomb", std::pair<int, int>{0, 10000});
					current_fireball = "small-missile";
					current_fireball_count = 50;
				}
				void Restart() {
					health = max_health;
					current_strength = max_strength / 2;
				}
			};
		}
	}
}
#endif