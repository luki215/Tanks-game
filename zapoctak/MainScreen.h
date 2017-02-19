#pragma once
#ifndef tanks_main_screen_header
#define tanks_main_screen_header

#include "GameScreenable.h"
#include "TanksGameManager.h"
#include "Render.h"
#include "SDL.h"
#include "BaseComponent.h"
#include "BaseButton.h"
#include <vector>
#include <memory>


namespace TanksGame{
	namespace Screens {
		class MainScreen : public GameScreenable {
		private:
			TanksGame::TanksGameManager & game_mngr;
			TanksGame::Render & render;
			std::vector<std::unique_ptr<Components::BaseComponent>> components;

			void InitializeComponents() {

				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(game_mngr, GameStatusEnum::main_screen, "> Play <", BasicStructres::SizeAndPos{ 800,500,180,50 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(game_mngr, GameStatusEnum::main_screen, "? Help ?", BasicStructres::SizeAndPos{ 800,570,180,50 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
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
			MainScreen(TanksGame::TanksGameManager * game_manager) :game_mngr{ *game_manager }, render{ game_manager->GetRender() }{
				InitializeComponents();
			
			};
		};
	}
}

#endif