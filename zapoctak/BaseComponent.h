#pragma once
#ifndef tanks_base_component_header
#define tanks_base_component_header

#include "SDL.h"
namespace TanksGame {
	namespace Components {

		class BaseComponent {
		protected:
			TanksGameManager & game_mngr;
			SDL_Renderer * renderer;
		public:
			virtual ~BaseComponent() {};
			virtual void Render() = 0;
			virtual void ProcessEvent(SDL_Event &e) = 0;
			BaseComponent(TanksGameManager & game_mngr) :game_mngr{ game_mngr }, renderer{ game_mngr.GetRender().GetRenderer() }{};
		};

	}
}

#endif