#include "TanksAppManager.h"

#include "MainScreen.h"
#include "GameScreen.h"
#include "NewGameScreen.h"

void TanksGame::TanksAppManager::LoadGameScreens()
{
	screens.emplace(AppStatusEnum::main_screen, std::make_unique<Screens::MainScreen>(*this));
	//screens.emplace(AppStatusEnum::new_game, std::make_unique<Screens::NewGameScreen>(*this));
	screens.emplace(AppStatusEnum::game, std::make_unique<Screens::GameScreen>(*this));
}
