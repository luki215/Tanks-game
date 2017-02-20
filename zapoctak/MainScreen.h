#pragma once
#ifndef tanks_main_screen_header
#define tanks_main_screen_header

#include "GameScreenable.h"
#include "TanksAppManager.h"
#include <SFML/Window.hpp>
#include "BaseComponent.h"
#include "BaseButton.h"
#include <vector>
#include <memory>


namespace TanksGame{
	namespace Screens {
		class MainScreen : public GameScreenable {
		private:
			TanksGame::TanksAppManager & app_mngr;
			sf::RenderWindow & window;
			std::vector<std::unique_ptr<Components::BaseComponent>> components;

			void InitializeComponents() {

				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, AppStatusEnum::game, "> Play <", BasicStructres::SizeAndPos{ 800,500,180,50 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, AppStatusEnum::main_screen, "? Help ?", BasicStructres::SizeAndPos{ 800,570,180,50 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
			}

		public:
			// Inherited via GameScreenable
			virtual void Render() override {
				window.clear(sf::Color::White);
				for (auto & component : components) {
					component->Render();
				}
			};
			virtual void HandleEvent(sf::Event & e) override {
				for (auto & component : components) {
					component->ProcessEvent(e);
				}
			}
			MainScreen(TanksGame::TanksAppManager & game_manager) :app_mngr{ game_manager }, window{ game_manager.GetWindow() }{
				InitializeComponents();
			
			};
		};
	}
}

#endif