
#include "TanksAppManager.h"
#include "GameManager.h"
#include <iostream>
#include "GameBaseComponent.h"
namespace TanksGame {

	std::array<std::pair<int, Components::Game::GameBaseComponent *> , TanksAppManager::scr_width + 1>& TanksGame::GameManager::GetCollisionLine()
	{
		
		for (auto & col_point : collision_line) 
			col_point = std::make_pair<int, Components::Game::GameBaseComponent *>(INT_MAX, NULL);

		for (auto & component : components) {
			int i = 0;
			auto it_end = component.second->GetTopCollosionLine().end();
			for (auto it = component.second->GetTopCollosionLine().begin(); it != it_end; ++it, i++)
			{
				if (*it > 2000)
					std::cout << "";
 				if (collision_line[i].first > *it )
					collision_line[i] = std::make_pair(*it, &*component.second);
			}

		}
		return collision_line;
	}
} 