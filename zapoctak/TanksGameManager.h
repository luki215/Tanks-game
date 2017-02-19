#pragma once
#ifndef tanks_game_manager_header
#define tanks_game_manager_header

#include "SDL.h"
#include "Render.h"
#include <map>
#include <memory>


#include "GameScreenable.h"


namespace TanksGame {

	//Game can't be in invalid status, invalid is just default value
	enum class GameStatusEnum{main_screen, help, player_settings, tanks_settings, game, quit, invalid};

	class TanksGameManager {
		using screen_ptr = std::unique_ptr<Screens::GameScreenable>;
		using screens_map = std::map<GameStatusEnum, screen_ptr>;
	private:
		GameStatusEnum status;
		Render render{1200,900};
		Screens::GameScreenable * current_screen;
		screens_map screens;

		void LoadGameScreens();
		
		

	public:
		
		TanksGameManager() { LoadGameScreens(); };
		void Run() {
			SwitchGameStatusTo(GameStatusEnum::main_screen);

			while (status != GameStatusEnum::quit)
			{
				SDL_Event e;
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						status = GameStatusEnum::quit;
					}

					current_screen->HandleEvent(e);
				}

				//Clear screen
				SDL_SetRenderDrawColor(render.GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(render.GetRenderer());

				current_screen->Render();

				SDL_SetRenderDrawBlendMode(render.GetRenderer(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
				//Update screen
				SDL_RenderPresent(render.GetRenderer());
			}


		}

		void SwitchGameStatusTo(GameStatusEnum status) {
			if (status != GameStatusEnum::invalid) {
				this->status = status;
				current_screen = screens.at(status).get();

			}
		}

		Render & GetRender() {
			return render;
		}


		
	};




}

#endif