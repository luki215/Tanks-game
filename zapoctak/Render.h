/*#pragma once
#ifndef tanks_render_header
#define tanks_render_header


#include <iostream>
#include "SDL.h"
#include "Exceptions.h"
#include "SDL_ttf.h"

namespace TanksGame {


	class Render {
		const int SCREEN_WIDTH;
		const int SCREEN_HEIGHT;
		SDL_Window* window_ = NULL;
		SDL_Renderer* renderer_ = NULL;

	public:
		Render(int screen_width, int screen_height) : SCREEN_WIDTH{ screen_width }, SCREEN_HEIGHT{ screen_height } {

			//The surface contained by the window
			SDL_Surface* screenSurface = NULL;

			//Initialize SDL
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
				throw CannotInitSDLException{ SDL_GetError() };

			//Create window
			window_ = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

			if (window_ == NULL)
				throw CannotInitSDLException{ SDL_GetError() };


			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
			if (renderer_ == NULL)
				throw CannotInitSDLException{ SDL_GetError() };

			TTF_Init();


		}

		SDL_Renderer * GetRenderer() {
			return renderer_;
		}


		~Render() {

			SDL_DestroyRenderer(renderer_);
			SDL_DestroyWindow(window_);
			window_ = NULL;
			renderer_ = NULL;

			TTF_Quit();
			SDL_Quit();
		}
	};

}
#endif // !tanks_render_header
*/