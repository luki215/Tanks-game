#pragma once
#pragma once
#ifndef tanks_components_game_tank_properties_header
#define tanks_components_game_tank_properties_header

#include "BasicStructures.h"
#include <map>
namespace TanksGame {
	namespace Components {
		namespace Game {
			struct TankProperties {
				using s_uint = uint_least16_t;
				uint_least8_t player;
				s_uint max_health;
				s_uint health;
				s_uint max_fuel;
				s_uint max_speed;
				s_uint max_strength;
				BasicStructres::Color color;
				int init_x_position;
				std::map<std::string, s_uint> fireballs;
			public:
				TankProperties(uint_least8_t player, s_uint x_position) :player{ player }, max_health{ 100 }, health{ 100 }, max_fuel{ 300 }, max_speed{ 2 }, max_strength{ 100 }, color{ BasicStructres::Color{0x000000} }, init_x_position{ x_position }, fireballs{ std::map<std::string, s_uint>{} } {};
			};
		}
	}
}
#endif