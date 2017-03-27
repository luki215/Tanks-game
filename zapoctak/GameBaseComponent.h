#pragma once
#ifndef tanks_game_base_component_header
#define tanks_game_base_component_header


#include <SFML/Window.hpp>
#include "BaseComponent.h"
#include "GameManager.h"

namespace TanksGame {
	class GameManager;

	namespace Components {
		namespace Game {
			class GameBaseComponent: public BaseComponent {
			protected:
				GameManager & manager;
			public:
				virtual ~GameBaseComponent() {};
				virtual void Render() = 0;
				virtual void ProcessEvent(sf::Event &e) = 0;
				virtual std::string Type() = 0;
				virtual void CollideWith(GameBaseComponent *component) = 0;
				virtual std::array<int, TanksAppManager::scr_width+1> const & GetTopCollosionLine() = 0;
				GameBaseComponent(TanksAppManager & app_mngr, GameManager & game_manager) :BaseComponent{ app_mngr }, manager{ game_manager } {};
			};
		}
	}
}

#endif