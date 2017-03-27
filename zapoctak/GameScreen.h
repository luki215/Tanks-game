#pragma once
#ifndef tanks_game_screen_header
#define tanks_game_screen_header

#include <SFML/Window.hpp>
#include "GameScreenable.h"
#include "TanksAppManager.h"
#include "BaseComponent.h"
#include "BaseButton.h"
#include "TextComponent.h"
#include "Landscape.h"
#include "Tank.h"
#include <map>
#include <memory>
#include "GameManager.h"

#include "ProgressBarVertical.h"
namespace TanksGame {
	namespace Screens {

		class GameScreen : public GameScreenable {
		private:
			TanksGame::TanksAppManager & app_mngr;
			sf::RenderWindow & window;
			GameManager manager{app_mngr};

			std::vector<std::unique_ptr<Components::BaseComponent>> components;

			void InitializeComponents() {				
				manager.InsertComponent("landscape", std::make_unique<Components::Game::Landscape>(app_mngr, manager));



				int i = 0;
				for (auto && player : app_mngr.GetPlayers()) {
					manager.InsertComponent("tank_" + player.name, std::make_unique<Components::Game::Tank>(app_mngr, manager, player.tank));
					
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, player.name + ":", BasicStructres::SizeAndPos(20 + i *600, 30, 20, 20), &player.tank.color));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Health", BasicStructres::SizeAndPos(160 + i *600, 5, 20, 10), BasicStructres::Color{ 0x000000 }));
					components.emplace_back( std::make_unique<Components::Others::ProgressBarVertical>(app_mngr,  BasicStructres::SizeAndPos(170 + i*600, 20, 30, 50), BasicStructres::Color{ 0xbf0303 }, player.tank.health, player.tank.max_health  ));
				
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Strength", BasicStructres::SizeAndPos(210 + i *600, 5, 20, 10), BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::ProgressBarVertical>(app_mngr, BasicStructres::SizeAndPos(220 + i *600, 20, 30, 50), BasicStructres::Color{ 0x007f10 }, player.tank.current_strength, player.tank.max_strength));

					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Fuel", BasicStructres::SizeAndPos(273 + i *600, 5, 20, 10), BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::ProgressBarVertical>(app_mngr, BasicStructres::SizeAndPos(270 + i *600, 20, 30, 50), BasicStructres::Color{ 0x002e7f }, player.tank.fuel, player.tank.max_fuel));

					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Ammo", BasicStructres::SizeAndPos(403 + i *600, 5, 20, 10), BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, &player.tank.current_fireball, BasicStructres::SizeAndPos(320 + i * 600, 25, 20, 15), BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, &player.tank.current_fireball_count, BasicStructres::SizeAndPos(460 + i * 600, 25, 20, 15), BasicStructres::Color{ 0x000000 }));


					i++;
				}



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
				for (auto && component : components) {
					component->Render();
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
			GameScreen(TanksGame::TanksAppManager &  game_manager) :app_mngr{ game_manager }, window{ game_manager.GetWindow() } {
				InitializeComponents();
			};

		};
	}
}

#endif