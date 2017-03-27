#pragma once
#ifndef tanks_new_game_screen_header
#define tanks_new_game_screen_header

#include "GameScreenable.h"
#include "TanksAppManager.h"
#include <SFML/Window.hpp>
#include "BaseButton.h"
#include "TextComponent.h"
#include <vector>
#include <memory>


namespace TanksGame {
	namespace Screens {
		class NewGameScreen	: public BasicStaticScreen{
		protected:
			// Inherited via BasicStaticScreen
			virtual void InitializeComponents() override {
				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Choose player colours", BasicStructres::SizeAndPos{ 100,50,100,60 }, BasicStructres::Color{ 0x000000 }));
				
				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Player 1:", BasicStructres::SizeAndPos{ 130,200,100,30 }, BasicStructres::Color{ 0x000000 }));
				
				//player 1 colors
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[0].tank.color = BasicStructres::Color{ 0xbf0303 }; (*((Components::Others::TextComponent*) (this->GetComponents()[1]).get())).ChangeTextColor(BasicStructres::Color{ 0xbf0303 }); 	}, "", BasicStructres::SizeAndPos{ 310,205,30,30 }, BasicStructres::Color{ 0xbf0303 }, BasicStructres::Color{ 0xbf0303 }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[0].tank.color = BasicStructres::Color{ 0x007f10 }; (*((Components::Others::TextComponent*) (this->GetComponents()[1]).get())).ChangeTextColor(BasicStructres::Color{ 0x007f10 }); 	}, "", BasicStructres::SizeAndPos{ 350,205,30,30 }, BasicStructres::Color{ 0x007f10 }, BasicStructres::Color{ 0x007f10 }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[0].tank.color = BasicStructres::Color{ 0x002e7f }; (*((Components::Others::TextComponent*) (this->GetComponents()[1]).get())).ChangeTextColor(BasicStructres::Color{ 0x002e7f }); 	}, "", BasicStructres::SizeAndPos{ 390,205,30,30 }, BasicStructres::Color{ 0x002e7f }, BasicStructres::Color{ 0x002e7f }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[0].tank.color = BasicStructres::Color{ 0x7f006e }; (*((Components::Others::TextComponent*) (this->GetComponents()[1]).get())).ChangeTextColor(BasicStructres::Color{ 0x7f006e }); 	}, "", BasicStructres::SizeAndPos{ 430,205,30,30 }, BasicStructres::Color{ 0x7f006e }, BasicStructres::Color{ 0x7f006e }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[0].tank.color = BasicStructres::Color{ 0xeaae46 }; (*((Components::Others::TextComponent*) (this->GetComponents()[1]).get())).ChangeTextColor(BasicStructres::Color{ 0xeaae46 }); 	}, "", BasicStructres::SizeAndPos{ 470,205,30,30 }, BasicStructres::Color{ 0xeaae46 }, BasicStructres::Color{ 0xeaae46 }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[0].tank.color = BasicStructres::Color{ 0x000000 }; (*((Components::Others::TextComponent*) (this->GetComponents()[1]).get())).ChangeTextColor(BasicStructres::Color{ 0x000000 }); 	}, "", BasicStructres::SizeAndPos{ 510,205,30,30 }, BasicStructres::Color{ 0x000000 }, BasicStructres::Color{ 0x000000 }));

				components.emplace_back(std::make_unique<Components::Others::TextComponent>(app_mngr, "Player 2:", BasicStructres::SizeAndPos{ 130,260,100,30 }, BasicStructres::Color{ 0x000000 }));

				//player 2 colors
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[1].tank.color = BasicStructres::Color{ 0xbf0303 }; (*((Components::Others::TextComponent*) (this->GetComponents()[8]).get())).ChangeTextColor(BasicStructres::Color{ 0xbf0303 }); 	}, "", BasicStructres::SizeAndPos{ 310,265,30,30 }, BasicStructres::Color{ 0xbf0303 }, BasicStructres::Color{ 0xbf0303 }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[1].tank.color = BasicStructres::Color{ 0x007f10 }; (*((Components::Others::TextComponent*) (this->GetComponents()[8]).get())).ChangeTextColor(BasicStructres::Color{ 0x007f10 }); 	}, "", BasicStructres::SizeAndPos{ 350,265,30,30 }, BasicStructres::Color{ 0x007f10 }, BasicStructres::Color{ 0x007f10 }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[1].tank.color = BasicStructres::Color{ 0x002e7f }; (*((Components::Others::TextComponent*) (this->GetComponents()[8]).get())).ChangeTextColor(BasicStructres::Color{ 0x002e7f }); 	}, "", BasicStructres::SizeAndPos{ 390,265,30,30 }, BasicStructres::Color{ 0x002e7f }, BasicStructres::Color{ 0x002e7f }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[1].tank.color = BasicStructres::Color{ 0x7f006e }; (*((Components::Others::TextComponent*) (this->GetComponents()[8]).get())).ChangeTextColor(BasicStructres::Color{ 0x7f006e }); 	}, "", BasicStructres::SizeAndPos{ 430,265,30,30 }, BasicStructres::Color{ 0x7f006e }, BasicStructres::Color{ 0x7f006e }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[1].tank.color = BasicStructres::Color{ 0xeaae46 }; (*((Components::Others::TextComponent*) (this->GetComponents()[8]).get())).ChangeTextColor(BasicStructres::Color{ 0xeaae46 }); 	}, "", BasicStructres::SizeAndPos{ 470,265,30,30 }, BasicStructres::Color{ 0xeaae46 }, BasicStructres::Color{ 0xeaae46 }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() { app_mngr.GetPlayers()[1].tank.color = BasicStructres::Color{ 0x000000 }; (*((Components::Others::TextComponent*) (this->GetComponents()[8]).get())).ChangeTextColor(BasicStructres::Color{ 0x000000 }); 	}, "", BasicStructres::SizeAndPos{ 510,265,30,30 }, BasicStructres::Color{ 0x000000 }, BasicStructres::Color{ 0x000000 }));



				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::tanks_settings); }, "Play", BasicStructres::SizeAndPos{ 800,500,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::main_screen); }, "Back", BasicStructres::SizeAndPos{ 800,580,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				components.emplace_back(std::make_unique<Components::Buttons::BaseButton>(app_mngr, [&]() {app_mngr.SwitchGameStatusTo(AppStatusEnum::help); }, "Help", BasicStructres::SizeAndPos{ 800,660,220,60 }, BasicStructres::Color{ 0x42a500 }, BasicStructres::Color{ 0xffffff }));
				
					
			}

		public:
			NewGameScreen(TanksGame::TanksAppManager & game_manager) :BasicStaticScreen(game_manager) {
				auto && players = game_manager.GetPlayers();
				players.emplace_back(Components::Game::Player{ "Player 1", Components::Game::TankProperties{0, 100}, 10000 });
				players.emplace_back(Components::Game::Player{ "Player 2", Components::Game::TankProperties{1, 200}, 10000 });
				
				InitializeComponents();
			}




		};
	}
}

#endif