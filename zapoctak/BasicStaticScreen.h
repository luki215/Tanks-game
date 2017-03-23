#pragma once
#ifndef tanks_basic_static_screen_header
#define tanks_basic_static_screen_header

#include "GameScreenable.h"
#include "TanksAppManager.h"
#include <SFML/Window.hpp>
#include "BaseComponent.h"
#include "BaseButton.h"
#include <vector>
#include <memory>


namespace TanksGame {
	namespace Screens {
		class BasicStaticScreen : public GameScreenable {
		protected:
			virtual void InitializeComponents() = 0;

			TanksGame::TanksAppManager & app_mngr;
			sf::RenderWindow & window;
			std::vector<std::unique_ptr<Components::BaseComponent>> components;
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
			BasicStaticScreen(TanksGame::TanksAppManager & game_manager) :app_mngr{ game_manager }, window{ game_manager.GetWindow() } {};
			virtual ~BasicStaticScreen() {};
		};
	}
}

#endif