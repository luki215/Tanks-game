#pragma once
#ifndef tanks_game_screen_header
#define tanks_game_screen_header

#include <SFML/Window.hpp>
#include "GameScreenable.h"
#include "TanksAppManager.h"
#include "BaseComponent.h"
#include "BaseButton.h"
#include "Landscape.h"
#include "Tank.h"
#include <map>
#include <memory>
#include "GameManager.h"

namespace TanksGame {
	namespace Screens {

		/*TODO: New class player, it has property TankProperties, where all tank settings of player will be stored. pointer to this var will be sent to each tank instance
			and then in HandleEvent tank components will be checked, if they belong to current player. 

			Then these settings save to file. 
			
		*/

		class GameScreen : public GameScreenable {
		private:
			TanksGame::TanksAppManager & app_mngr;
			sf::RenderWindow & window;
			GameManager manager{};
			void InitializeComponents() {				
				manager.InsertComponent("landscape", std::make_unique<Components::Game::Landscape>(app_mngr, manager));

				auto tank_1_prop = Components::Game::TankProperties{};
				tank_1_prop.player = 1;
				tank_1_prop.color = 0x000000;
				tank_1_prop.init_x_position = 30;
				tank_1_prop.fireballs.emplace("Small", 30);
				tank_1_prop.health = 100;
				tank_1_prop.max_fuel = 100;
				tank_1_prop.max_speed = 2;
				tank_1_prop.max_strength = 100;

				auto tank_2_prop = tank_1_prop;
				tank_2_prop.player = 2;
				tank_2_prop.init_x_position = 900;
				tank_2_prop.color = 0xff0000;

				manager.InsertComponent("tank", std::make_unique<Components::Game::Tank>(app_mngr, manager, tank_1_prop));
				manager.InsertComponent("tank2", std::make_unique<Components::Game::Tank>(app_mngr, manager, tank_2_prop));
			}

		public:
			// Inherited via GameScreenable
			virtual void Render() override {
				int i = 0;
				for (auto && it = manager.GetComponents().begin(); it != manager.GetComponents().end(); ++it ) {
					int count = manager.GetComponents().size();
					it->second->Render();
					if (manager.GetComponents().size() != count) {
						it = manager.GetComponents().begin() + i;
						if (it == manager.GetComponents().end())
							break;
					}
					i++;
				}
			};
			virtual void HandleEvent(sf::Event & e) override {
				int i = 0;
				for (auto && it = manager.GetComponents().begin(); it != manager.GetComponents().end(); ++it) {
					int count = manager.GetComponents().size();
					it->second->ProcessEvent(e);
					if (manager.GetComponents().size() != count) it = manager.GetComponents().begin() + i+1;
					i++;
				}
			}
			GameScreen(TanksGame::TanksAppManager & game_manager) :app_mngr{ game_manager }, window{ game_manager.GetWindow() } {
				InitializeComponents();
			};

		};
	}
}

#endif