#include "TanksGameManager.h"

#include "MainScreen.h"
#include "GameScreen.h"

void TanksGame::TanksGameManager::LoadGameScreens()
{
	screens.emplace(GameStatusEnum::main_screen, std::make_unique<Screens::MainScreen>(this));
	screens.emplace(GameStatusEnum::game, std::make_unique<Screens::GameScreen>(this));
}
