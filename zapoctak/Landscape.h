#pragma once
#ifndef tanks_components_game_landscape_header
#define tanks_components_game_landscape_header

#include "GameScreenable.h"
#include "TanksGameManager.h"
#include "Render.h"
#include "SDL.h"
#include "BaseComponent.h"
#include "BasicStructures.h"
#include <vector>
namespace TanksGame {
	namespace Components {
		namespace Game {

			class Landscape : public BaseComponent {
				using Point = BasicStructres::Point;
				std::vector<Point> ground{ Point{0, 850}, Point{80, 850}, Point{200, 700}, Point{400, 880}, Point{ 450, 800 }, Point{ 500, 850 }, Point{ 600, 850 }, Point{ 700, 500 }, Point{ 750, 600 }, Point{ 800, 550 }, Point{ 950, 800 }, Point{ 1280, 700 } };


			public:
				// Inherited via BaseComponent
				virtual void Render() override {

					auto color = BasicStructres::Color{ 0x00b712 };
					SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);

					if (ground.size() < 2)
						throw TooFewGroundPointsException();
					auto prev_point = ground.begin();
					for (auto && point = ground.begin() + 1; point != ground.end(); ++point) {
						SDL_RenderDrawLine(renderer, prev_point->X, prev_point->Y, point->X, point->Y);
						prev_point = point;
					}
				}

				virtual void ProcessEvent(SDL_Event & e) override {};
				Landscape(TanksGameManager & game_mngr) :BaseComponent(game_mngr) { };

			};

		}
	}
}
#endif