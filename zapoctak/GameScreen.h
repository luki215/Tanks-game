#pragma once
#ifndef tanks_game_screen_header
#define tanks_game_screen_header

#include "GameScreenable.h"
#include "TanksGameManager.h"
#include "Render.h"
#include "SDL.h"
#include "BaseComponent.h"
#include "BaseButton.h"
#include "Landscape.h"
#include "Tank.h"
#include <vector>
#include <memory>


namespace TanksGame {
	namespace Screens {
		class GameScreen : public GameScreenable {
		private:
			TanksGame::TanksGameManager & game_mngr;
			TanksGame::Render & render;
			std::vector<std::unique_ptr<Components::BaseComponent>> components;

			void InitializeComponents() {
				components.emplace_back(std::make_unique<Components::Game::Landscape>(game_mngr));
				components.emplace_back(std::make_unique<Components::Game::Tank>(game_mngr));
			}

		public:
			// Inherited via GameScreenable
			virtual void Render() override {
				for (auto & component : components) {
					component->Render();
				}
			};
			virtual void HandleEvent(SDL_Event & e) override {
				for (auto & component : components) {
					component->ProcessEvent(e);
				}
			}
			GameScreen(TanksGame::TanksGameManager * game_manager) :game_mngr{ *game_manager }, render{ game_manager->GetRender() } {
				InitializeComponents();

			};
		};
	}
}

#endif