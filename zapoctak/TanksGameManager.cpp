#include "TanksGameManager.h"

#include "MainScreen.h"

void TanksGame::TanksGameManager::LoadGameScreens()
{
	screens.emplace(GameStatusEnum::main_screen, std::make_unique<Screens::MainScreen>(this));
}
