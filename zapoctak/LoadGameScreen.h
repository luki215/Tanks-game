#pragma once
#ifndef tanks_load_game_screen_header
#define tanks_load_game_screen_header

#include "GameScreenable.h"
#include "TanksAppManager.h"
#include <SFML/Window.hpp>
#include "BaseButton.h"
#include "TextComponent.h"
#include <vector>
#include <memory>
#include "BasicStaticScreen.h"

namespace TanksGame {
	namespace Screens {
		class LoadGameScreen : public BasicStaticScreen {
		protected:
			// Inherited via BasicStaticScreen
			virtual void InitializeComponents() override {
				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Load game - choose slot:", BasicStructres::SizeAndPos{ 100,50,100,60 }, BasicStructres::Color{ 0x000000 }));

				for (int i = 0; i < 5; i++)
				{
					components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&, i]() { if (app_mngr.GetSavingSlots()[i] != "EMPTY") { app_mngr.LoadGame(i); app_mngr.SwitchGameStatusTo(AppStatusEnum::tanks_settings); } }, &app_mngr.GetSavingSlots()[i], BasicStructres::SizeAndPos{ 210 ,205 + 100 * i,300,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				}
				for (int i = 5; i < 10; i++)
				{
					components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&, i]() { if (app_mngr.GetSavingSlots()[i] != "EMPTY") { app_mngr.LoadGame(i); app_mngr.SwitchGameStatusTo(AppStatusEnum::tanks_settings); }}, &app_mngr.GetSavingSlots()[i], BasicStructres::SizeAndPos{ 610 ,205 + 100 * i - 500,300,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				}

				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::main_screen); }, "Back", BasicStructres::SizeAndPos{ 800,780,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));


			}


		public:


			LoadGameScreen(TanksGame::TanksAppManager & game_manager) :BasicStaticScreen(game_manager) {
				
				InitializeComponents();
			}




		};
	}
}

#endif