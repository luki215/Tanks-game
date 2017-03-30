#include "TanksAppManager.h"

#include "MainScreen.h"
#include "GameScreen.h"
#include "NewGameScreen.h"
#include "TankSettingsScreen.h"
#include "SaveGameScreen.h"
#include "LoadGameScreen.h"

void TanksGame::TanksAppManager::LoadGameScreens()
{
	screens.emplace(AppStatusEnum::main_screen, std::make_unique<Screens::MainScreen>(*this));
	screens.emplace(AppStatusEnum::new_game, std::make_unique<Screens::NewGameScreen>(*this));
	screens.emplace(AppStatusEnum::tanks_settings, std::make_unique<Screens::TankSettingsScreen>(*this));
	screens.emplace(AppStatusEnum::game, std::make_unique<Screens::GameScreen>(*this));
	screens.emplace(AppStatusEnum::save_game, std::make_unique<Screens::SaveGameScreen>(*this));
	screens.emplace(AppStatusEnum::load_game, std::make_unique<Screens::LoadGameScreen>(*this));
}
