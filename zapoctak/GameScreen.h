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
				manager.InsertComponent("tank", std::make_unique<Components::Game::Tank>(app_mngr, manager));
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