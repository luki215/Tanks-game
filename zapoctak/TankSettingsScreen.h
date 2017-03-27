#pragma once
#ifndef tanks_tank_settings_screen_header
#define tanks_tank_settings_screen_header

#include "GameScreenable.h"
#include "TanksAppManager.h"
#include "BasicStaticScreen.h"
#include <SFML/Window.hpp>
#include "BaseButton.h"
#include "TextComponent.h"
#include "ProgressBarLargeHorizontal.h"


namespace TanksGame {
	namespace Screens {
		class TankSettingsScreen : public BasicStaticScreen {
		protected:
			// Inherited via BasicStaticScreen
			virtual void InitializeComponents() override {
				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Tank settings", BasicStructres::SizeAndPos{ 100,50,100,60 }, BasicStructres::Color{ 0x000000 }));
				
				//Player 1
				auto && players = app_mngr.GetPlayers();
				int i = 0;
				for (auto && player : players) {
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, player.name, BasicStructres::SizeAndPos{500*i+ 130,200,100,30 }, &players[i].tank.color));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Money:", BasicStructres::SizeAndPos{ 500 * i + 140,250,100, 20 }, BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, &(player.money), BasicStructres::SizeAndPos{ 500 * i + 230,250,100,20 }, BasicStructres::Color{ 0x000000 }));

					//fuel
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Fuel:", BasicStructres::SizeAndPos{ 500 * i + 140,280,100, 20 }, BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::ProgressBarLargeHorizontal>(app_mngr, BasicStructres::SizeAndPos{ 500 * i + 230,285,100,20 }, BasicStructres::Color{ 0x42a500 }, player.tank.fuel, player.tank.max_fuel));
					components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { if (player.tank.max_fuel - 50 >= player.tank.fuel && player.money >500) { player.money -= 500; player.tank.fuel += 50; } else if(player.tank.max_fuel > player.tank.fuel && player.money>=player.tank.max_fuel - player.tank.fuel * 10) { player.money -= player.tank.max_fuel - player.tank.fuel * 10; player.tank.fuel = player.tank.max_fuel; } }, "+50", BasicStructres::SizeAndPos{ 500 * i + 340,280,30,30 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "500", BasicStructres::SizeAndPos{ 500 * i + 380,280,100, 20 }, BasicStructres::Color{ 0xff0000 }));
					
					//max strength
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Max strength:", BasicStructres::SizeAndPos{ 500 * i + 140,310,100, 20 }, BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, &(player.tank.max_strength), BasicStructres::SizeAndPos{ 500 * i + 300,310,100, 20 }, BasicStructres::Color{ 0x000000 }));
					components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { if (player.money >= 10000) { player.money -= 10000; player.tank.max_strength += 20; } }, "+20", BasicStructres::SizeAndPos{ 500 * i + 340,310,30,30 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "10000", BasicStructres::SizeAndPos{ 500 * i + 380,310,100, 20 }, BasicStructres::Color{ 0xff0000 }));


					//shoots
					
					components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Missiles:", BasicStructres::SizeAndPos{ 500 * i + 140,400,100, 25 }, BasicStructres::Color{ 0x000000 }));

					int j = 0;
					for (auto && fireball : player.tank.fireballs) {
						components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, fireball.first + ":", BasicStructres::SizeAndPos{ 500 * i + 150,440 + j * 40,100, 20 }, BasicStructres::Color{ 0x000000 }));
						components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, &fireball.second.first, BasicStructres::SizeAndPos{ 500 * i + 350,440 + j*40,100, 20 }, BasicStructres::Color{ 0x000000 }));
						
						components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { if (player.money >= 10 * fireball.second.second) { player.money -= fireball.second.second * 10; fireball.second.first += 10; } }, "+10", BasicStructres::SizeAndPos{ 500 * i + 410,440 + j * 40,30,30 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
						components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, std::to_string(fireball.second.second)+"/ks", BasicStructres::SizeAndPos{ 500 * i + 450,440 + j * 40,100, 20 }, BasicStructres::Color{ 0xff0000 }));

						j++;
					}

					i++;
				}
				
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::save_game); }, "Save Game", BasicStructres::SizeAndPos{ 400,800,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::game); }, "Play", BasicStructres::SizeAndPos{ 700,800,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));


			}

		public:			
			TankSettingsScreen(TanksGame::TanksAppManager & game_manager) : BasicStaticScreen(game_manager) {
				InitializeComponents();
			};




		};
	}
}

#endif