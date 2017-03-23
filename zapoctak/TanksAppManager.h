#pragma once
#ifndef tanks_app_manager_header
#define tanks_app_manager_header

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Render.h"
#include <map>
#include <memory>
#include "GameScreenable.h"


/* Handles whole program*/
namespace TanksGame {

	//Game can't be in invalid status, invalid is just default value
	enum class AppStatusEnum{main_screen, help, load_game, new_game, tanks_settings, game, invalid};

	class TanksAppManager {
		using screen_ptr = std::unique_ptr<Screens::GameScreenable>;
		using screens_map = std::map<AppStatusEnum, screen_ptr>;
	private:
		AppStatusEnum status;
		sf::RenderWindow  window;
		Screens::GameScreenable * current_screen;
		screens_map screens;

		void LoadGameScreens();
		
		

	public:
		static const unsigned int scr_height = 900;
		static const unsigned int scr_width = 1280;
		TanksAppManager() { 

			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;
			window.create( sf::VideoMode{ scr_width, scr_height }, "Tanks", sf::Style::Close, settings ); 
			LoadGameScreens(); 
		};
		void Run() {
			SwitchGameStatusTo(AppStatusEnum::main_screen);


			// run the program as long as the window is open
			while (window.isOpen())
			{
				// check all the window's events that were triggered since the last iteration of the loop
				sf::Event event;
				while (window.pollEvent(event))
				{
					// "close requested" event: we close the window
					if (event.type == sf::Event::Closed)
						window.close();

					current_screen->HandleEvent(event);
				}
				window.clear(sf::Color::Black);

				current_screen->Render();

				window.display();
			}

		}

		void SwitchGameStatusTo(AppStatusEnum status) {
			if (status != AppStatusEnum::invalid) {
				this->status = status;
				current_screen = screens.at(status).get();

			}
		}

		sf::RenderWindow & GetWindow() {
			return window;
		}


		
	};




}

#endif