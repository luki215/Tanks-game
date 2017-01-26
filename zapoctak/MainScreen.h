#pragma once
#ifndef tanks_main_screen_header
#define tanks_main_screen_header

#include "GameScreenable.h"
#include "TanksGameManager.h"
#include "Render.h"
#include "SDL.h"

namespace TanksGame{
	namespace Screens {
		class MainScreen : public GameScreenable {
		private:
			TanksGame::TanksGameManager * game_mngr;
			TanksGame::Render * render;

		public:
			// Inherited via GameScreenable
			virtual void Render() override {
				
				SDL_Rect fillRect = { 400, 400, 100, 100 };
				SDL_SetRenderDrawColor(render->GetRenderer(), 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(render->GetRenderer(), &fillRect);

				fillRect = { 400, 500, 100, 100 };
				SDL_SetRenderDrawColor(render->GetRenderer(), 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderFillRect(render->GetRenderer(), &fillRect);


			};
			virtual void HandleEvent(SDL_Event & e) override {

			}
			MainScreen(TanksGame::TanksGameManager * game_manager) :game_mngr{ game_manager }{
				render = game_manager->GetRender(); 
			
			};
		};
	}
}

#endif