#pragma once
#ifndef tanks_game_screenable_header
#define tanks_game_screenable_header


#include "SDL.h"
namespace TanksGame {
	namespace Screens {
		class GameScreenable {
		public:
			virtual void Render() = 0;
			virtual void HandleEvent(SDL_Event &e) = 0;
			virtual ~GameScreenable() {};
		};
	}
}


#endif