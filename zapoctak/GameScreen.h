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

		

		class GameScreen : public GameScreenable {
		private:
			enum class GameStatusEnum{player_move, shot, collision, pause};
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
				for (auto & component : manager.GetComponents()) {
					component.second->Render();
				}
			};
			virtual void HandleEvent(sf::Event & e) override {
				for (auto & component : manager.GetComponents()) {
					component.second->ProcessEvent(e);
				}
			}
			GameScreen(TanksGame::TanksAppManager & game_manager) :app_mngr{ game_manager }, window{ game_manager.GetWindow() } {
				InitializeComponents();
			};
		};
	}
}

#endif