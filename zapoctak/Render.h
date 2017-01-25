#pragma once
#ifndef tanks_render_header
#define tanks_render_header


#include <iostream>
#include "SDL.h";
#include "Exceptions.h";




class Render {


public:
	void Init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		const int SCREEN_WIDTH = 1200;
		const int SCREEN_HEIGHT = 900;

		SDL_Window* window = NULL;

		//The surface contained by the window
		SDL_Surface* screenSurface = NULL;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw CannotInitSDLException{ SDL_GetError() };
		}
		else
		{
			//Create window
			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

				//Update the surface
				SDL_UpdateWindowSurface(window);

				//Wait two seconds
				SDL_Delay(2000);
			}
		}
	}

	void Destroy() {

		SDL_Quit();
	}
};
	

#endif // !tanks_render_header
