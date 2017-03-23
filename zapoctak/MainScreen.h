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
			
			
		public:
			MainScreen(TanksGame::TanksAppManager & game_manager) :BasicStaticScreen(game_manager)  {
				InitializeComponents();
			}

			// Inherited via BasicStaticScreen
			virtual void InitializeComponents() override {

				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::game); }, "> Play <", BasicStructres::SizeAndPos{ 800,500,180,50 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::help); }, "? Help ?", BasicStructres::SizeAndPos{ 800,570,180,50 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));

			}
		

		};
	}
}

#endif