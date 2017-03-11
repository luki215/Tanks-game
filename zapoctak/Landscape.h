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
#include <cmath>
#include <array>
namespace TanksGame {
	namespace Components {
		namespace Game {

			class Landscape : public GameBaseComponent {
				using Point = BasicStructres::Point;
				std::vector<Point> ground{ Point{0, 850}, Point{80, 850}, Point{ 180, 700 }, Point{220, 700}, Point{400, 880}, Point{ 450, 800 }, Point{ 500, 850 }, Point{ 600, 850 }, Point{ 700, 500 }, Point{ 750, 600 }, Point{ 800, 550 }, Point{ 950, 800 }, Point{ 1280, 700 } };
				std::array<int, TanksAppManager::scr_width +1> top_collision_line;

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
				void GetYAndSlopeInPoint(int X, int & Y, int &slope) {				
					auto it_down = std::upper_bound(ground.begin(), ground.end(), Point{ X, 0 }, [](const Point & r, const Point & l) { return r.X < l.X; });
					auto it_up = std::lower_bound(ground.begin(), ground.end(), Point{ X, 0 }, [](const Point & r, const Point & l) { return r.X < l.X; });
					if (it_down == ground.begin())
					{
						slope = 0;
						Y = it_down->Y;
					}
					else {
						it_down--;
						double angle_rad = 0;
						if (it_up->X - it_down->X == 0)
							slope = 0;
						else {
							angle_rad = atan((double)(it_up->Y - it_down->Y) / (it_up->X - it_down->X));
							slope = angle_rad * 180 / 3.14;
						}

						Y = (tan(angle_rad) * (X - it_down->X)) + it_down->Y;


					}
				}
				virtual void ProcessEvent(sf::Event & e) override {};
				Landscape(TanksAppManager & app_mngr, GameManager & game_manager) :GameBaseComponent(app_mngr, game_manager) { 
					int border_index = 0;
					

					auto point_before = ground.begin();
					for (auto point = ground.begin() + 1; point != ground.end(); ++point) {
						int i;
						for (i = border_index; i <= point->X; i++) {
							double angle_rad = 0;
							if (point->X - point_before->X != 0)
								angle_rad = atan((double)(point->Y - point_before->Y) / (point->X - point_before->X));
							
							top_collision_line[i] = (tan(angle_rad) * (i - point_before->X)) + point_before->Y;
						}
						border_index = i;
						point_before = point;
					}
				};
				virtual std::array<int, TanksAppManager::scr_width+1> & GetTopCollosionLine() override {
					return top_collision_line;
				}
				virtual std::string Type() override {
					return "Landscape";
				}
				virtual void CollideWith(GameBaseComponent & component) override {
					//may write landscape destruction and modification after contact with other objects
				}
			};

		}
	}
}
#endif