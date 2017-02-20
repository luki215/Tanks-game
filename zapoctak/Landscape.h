#pragma once
#ifndef tanks_components_game_landscape_header
#define tanks_components_game_landscape_header

#include "GameScreenable.h"
#include "TanksAppManager.h"
#include "Render.h"
#include <SFML/Window.hpp>
#include "GameBaseComponent.h"
#include "BasicStructures.h"
#include <vector>
#include "Exceptions.h"
namespace TanksGame {
	namespace Components {
		namespace Game {

			class Landscape : public GameBaseComponent {
				using Point = BasicStructres::Point;
				std::vector<Point> ground{ Point{0, 850}, Point{80, 850}, Point{200, 700}, Point{400, 880}, Point{ 450, 800 }, Point{ 500, 850 }, Point{ 600, 850 }, Point{ 700, 500 }, Point{ 750, 600 }, Point{ 800, 550 }, Point{ 950, 800 }, Point{ 1280, 700 } };


			public:
				// Inherited via BaseComponent
				virtual void Render() override {
					window.clear(sf::Color::White);
					auto color = BasicStructres::Color{ 0x00b712 };
					sf::ConvexShape convex;
					convex.setPointCount(ground.size() + 2);
					convex.setFillColor(color);


					if (ground.size() < 2)
						throw TooFewGroundPointsException();
					//TODO Find clever way to draw ground properly
					convex.setPoint(0, sf::Vector2f(-2000, 5000));
					int i = 1;
					for (auto && point = ground.begin(); point != ground.end(); ++point, ++i) {
						convex.setPoint(i, sf::Vector2f(point->X, point->Y));
					}

					convex.setPoint(i, sf::Vector2f(3000, 5000));

					window.draw(convex);
				}

				virtual void ProcessEvent(sf::Event & e) override {};
				Landscape(TanksAppManager & app_mngr, GameManager game_manager) :GameBaseComponent(app_mngr, game_manager) { };

			};

		}
	}
}
#endif