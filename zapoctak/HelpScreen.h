#pragma once
#ifndef tanks_help_screen_header
#define tanks_help_screen_header

#include "BasicStaticScreen.h"
#include "BaseButton.h"
#include "TextComponent.h"
#include "TanksAppManager.h"
#include "BasicStructures.h"
#include <iostream>

namespace TanksGame {
	namespace Screens {
		class HelpScreen : public BasicStaticScreen {
		protected:
			// Inherited via BasicStaticScreen
			virtual void InitializeComponents() override {

				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Controlls:", BasicStructres::SizeAndPos{ 100,50,100,60 }, BasicStructres::Color{ 0x000000 }));
				
				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Space:  fire\n"
					"Left arrow:  move left\n"
					"Right arrow:  move right\n"
					"Up arrow:  move canon right\n"
					"Up down:  move canon left\n"
					"Pg down:  decrease fire strength\n"
					"Pg up:  increase fire strength\n"
					"Home:  prev weapon\n"
					"End:  next weapon\n"

					, BasicStructres::SizeAndPos{ 120,200,100, 30 }, BasicStructres::Color{ 0x000000 }));
				


				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::main_screen); }, "Back", BasicStructres::SizeAndPos{ 200,800,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));

			}

		public:
			HelpScreen(TanksGame::TanksAppManager & game_manager) :BasicStaticScreen(game_manager) {
				InitializeComponents();
			}




		};
	}
}

#endif