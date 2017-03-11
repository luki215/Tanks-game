#pragma once
#pragma once
#ifndef game_manager_header
#define game_manager_header
#include "GameBaseComponent.h"
#include <memory>
#include <array>
#include <string>

namespace TanksGame {

	namespace Components {
		namespace Game {
			class GameBaseComponent;
		}
	}
	struct GameEnviroment {
		const float gravity = 10;
		const float resistance =0.999;

	};
	class GameManager {
	private:
		using component = Components::Game::GameBaseComponent;
		using component_pair = std::pair<std::string, std::unique_ptr<component>>;
		std::vector<component_pair> components;
		std::array<std::pair<int, Components::Game::GameBaseComponent *>, TanksAppManager::scr_width + 1> collision_line;
		uint_least8_t current_player = 1;
		uint_least8_t players_count = 2;
		
	public:
		GameEnviroment env;
		enum class GameStatusEnum { player_move, shot, collision, pause };

		void InsertComponent(std::string identifier, std::unique_ptr<component> component) {
			components.push_back(component_pair{ identifier, std::move(component) });
		}
		void RemoveComponent(std::string identifier){
			auto it = find_if(components.begin(), components.end(), [identifier](const component_pair& element) { return element.first == identifier; });
			components.erase(it);
		}
		component & GetComponent(std::string identifier) {
			component & comp = *(find_if(components.begin(), components.end(), [identifier](const component_pair& element) { return element.first == identifier; })->second);

			return comp;
		}
		const std::vector<component_pair> & GetComponents() {
			return components;
		}
		std::array<std::pair<int, component *>, TanksAppManager::scr_width + 1> & GetCollisionLine();

		GameStatusEnum CurrentStatus() { return current_status; }
		void SetCurrentStatus(GameStatusEnum status) {
			if (status == GameStatusEnum::player_move)
				current_player = ((current_player) % players_count)+1;
			current_status = status;
		}
		uint_least8_t CurrentPlayer() const {
			return current_player;
		}

	private:
		GameStatusEnum current_status = GameStatusEnum::player_move;
	};
}

#endif