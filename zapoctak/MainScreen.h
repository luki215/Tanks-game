#pragma once
#ifndef tanks_main_screen_header
#define tanks_main_screen_header

#include "BasicStaticScreen.h"
#include "BaseButton.h"
#include "TanksAppManager.h"
#include "BasicStructures.h"
#include <iostream>

namespace TanksGame{
	namespace Screens {
		class MainScreen : public BasicStaticScreen {
		protected:	
			// Inherited via BasicStaticScreen
			virtual void InitializeComponents() override {

				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::new_game); }, "New game", BasicStructres::SizeAndPos{ 800,500,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::load_game); }, "Load game", BasicStructres::SizeAndPos{ 800,580,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::help); }, "Help", BasicStructres::SizeAndPos{ 800,660,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));

			}
			
		public:
			MainScreen(TanksGame::TanksAppManager & game_manager) :BasicStaticScreen(game_manager)  {
				InitializeComponents();
			}

		
		

		};
	}
}

#endif