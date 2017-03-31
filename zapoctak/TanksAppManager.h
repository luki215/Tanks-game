#pragma once
#ifndef tanks_app_manager_header
#define tanks_app_manager_header

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Render.h"
#include <map>
#include <array>
#include <memory>
#include "GameScreenable.h"
#include "Player.h"
#include <fstream>
#include "Exceptions.h"
#include <fstream>
#include <ctime>

/* Handles whole program*/
namespace TanksGame {

	//Game can't be in invalid status, invalid is just default value
	enum class AppStatusEnum{main_screen, help, load_game, save_game, new_game, tanks_settings, game, invalid};

	class TanksAppManager {
		using screen_ptr = std::unique_ptr<Screens::GameScreenable>;
		using screens_map = std::map<AppStatusEnum, screen_ptr>;
	private:
		AppStatusEnum status;
		sf::RenderWindow  window;
		Screens::GameScreenable * current_screen;
		screens_map screens;

		void LoadGameScreens();

		std::vector<Components::Game::Player> players;

		std::array<std::string, 10> saving_slots;
		
		void LoadSavingSlots() {
			for (int i = 0; i < 10; i++)
			{
				std::ifstream f("game-" + std::to_string(i) + ".save");
				if (f.good()) {
					std::getline(f, saving_slots[i]);
				}
				else
					saving_slots[i] = "EMPTY";
			}
		}
		

	public:
		static const unsigned int scr_height = 900;
		static const unsigned int scr_width = 1280;
		TanksAppManager() { 

			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;

			LoadSavingSlots();
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
			if (status == AppStatusEnum::new_game) {
				for (auto && player : players) {
					player.tank.HardRestart();
					player.money = 10000;
				}

			}
			if (status != AppStatusEnum::invalid) {
				this->status = status;
				current_screen = screens.at(status).get();

			}
		}


		void SaveGame(int slot) {
			std::ofstream save_file("game-"+std::to_string(slot)+".save");
			if (save_file.good()) {
				time_t t = time(0);   // get time now
				struct tm * now = localtime(&t);
				save_file << now->tm_mday << "." << now->tm_mon << "." << now->tm_year+1900 << "-" << now->tm_hour << ":" << now->tm_min;
				for (auto && player : players) {
					save_file << std::endl;
					save_file << player.name << std::endl;
					save_file << player.money << std::endl;
					save_file << player.tank.color.R << std::endl;
					save_file << player.tank.color.G << std::endl;
					save_file << player.tank.color.B << std::endl;
					save_file << player.tank.color.A << std::endl;
					save_file << player.tank.current_fireball << std::endl;
					save_file << player.tank.current_fireball_count << std::endl;
					save_file << player.tank.current_strength << std::endl;
					save_file << player.tank.fuel << std::endl;
					save_file << player.tank.health << std::endl;
					save_file << player.tank.init_x_position << std::endl;
					save_file << player.tank.max_fuel << std::endl;
					save_file << player.tank.max_health << std::endl;
					save_file << player.tank.max_speed << std::endl;
					save_file << player.tank.max_strength << std::endl;
					save_file << player.tank.player << std::endl;
					for (auto && record : player.tank.fireballs) {
						save_file << record.second.first << std::endl;
					}

				}
			}
			save_file.close();
			LoadSavingSlots();
		}
		void LoadGame(int slot) {
			std::ifstream load_file("game-" + std::to_string(slot) + ".save");

			if (load_file.good()) {
				std::string em;
				while (true) {
					if (!load_file.good()) {
							break;
					}
					for (auto && player : players) {
						
						char c;
						std::getline(load_file, em);
						std::getline(load_file, player.name);
						load_file >> player.money;
						load_file >> player.tank.color.R;
						load_file >> player.tank.color.G;
						load_file >> player.tank.color.B;
						load_file >> player.tank.color.A;
						std::getline(load_file, em);
						std::getline(load_file, player.tank.current_fireball);
						load_file >> player.tank.current_fireball_count;
						load_file >> player.tank.current_strength;
						load_file >> player.tank.fuel;
						load_file >> player.tank.health;
						load_file >> player.tank.init_x_position;
						load_file >> player.tank.max_fuel;
						load_file >> player.tank.max_health;
						load_file >> player.tank.max_speed;
						load_file >> player.tank.max_strength;
						load_file >> player.tank.player;
						for (auto && record : player.tank.fireballs) {
							load_file >> record.second.first;
						}
						getline(load_file, em);
					}
				}
			}
		}

		std::array<std::string, 10> & GetSavingSlots() {
			return saving_slots;
		}

		sf::RenderWindow & GetWindow() {
			return window;
		}

		std::vector<Components::Game::Player> & GetPlayers() {
			return players;
		}


		
	};




}

#endif