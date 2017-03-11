#pragma once
#ifndef tanks_components_game_fireball_header
#define tanks_components_game_fireball_header

#include <SFML/Window.hpp>
#include "GameBaseComponent.h"
#include <vector>
#include "BasicStructures.h"
#include "TanksAppManager.h"
#include <iostream>

namespace TanksGame {
	namespace Components {
		namespace Game {

			class FireballFactory {

			};


			class Fireball : public GameBaseComponent {
				using Pointf = BasicStructres::Pointf;
			private:
				Pointf pos;
				Pointf move_vector;
				sf::Clock clock; 
				sf::Time last_calculated_position_time;
				double weight = 10; 
				std::array<int, TanksAppManager::scr_width + 1> collision_arr;
				Pointf collision_point;
				GameBaseComponent * colliding_object = NULL;
				std::string identifier;

				Pointf CalculateNewPosition() {

					float v_x = move_vector.X/10;
					float v_y = move_vector.Y/10;

					Pointf new_pos;
					new_pos.X = pos.X + v_x;
					new_pos.Y = pos.Y + v_y;

					move_vector.Y += (manager.env.gravity * weight)/500;
					move_vector.Y *= manager.env.resistance;
					move_vector.X *= manager.env.resistance;

					clock.restart();

					return new_pos;
				}
				void InitCollisions(){
					auto enviroment_collision_line = manager.GetCollisionLine();
					auto move_vector_backup = move_vector;
					auto pos_backup = pos;
					auto pos_before = Pointf(pos);

					while (true) {
						pos = CalculateNewPosition();

						if (pos.Y > TanksAppManager::scr_height || pos.X < 0 || pos.X > TanksAppManager::scr_width) {
							collision_point = Pointf( (pos.X<0)? -1 : 1, 0);
							colliding_object = NULL;
							break;
						}
						if (enviroment_collision_line[pos.X].first <= pos.Y) {
							//Calculate exact point of collision - count line between pos_before and pos and then compare point by point with enviroment_collisoin_line

							if (pos_before.X > pos.X) {
								auto a = pos_before;
								pos_before = pos;
								pos = a;
							}							


							double angle_rad = 0;
							if (pos.X - pos_before.X != 0)
								angle_rad = atan((double)(pos.Y - pos_before.Y) / (pos.X - pos_before.X));

					
							for (int i = pos_before.X; i <= pos.X; ++i) {
								if (enviroment_collision_line[i].first <= pos.Y) {
									auto y = (tan(angle_rad) * (i - pos_before.X)) + pos_before.Y;
									collision_point = Pointf(i, y);
									colliding_object = enviroment_collision_line[i].second;
									goto break_while;
								}
							}
						}
						

						pos_before = pos;
					}
					break_while:
					pos = pos_backup;
					move_vector = move_vector_backup;
				}
			public:
				// Inherited via GameBaseComponent
				virtual void Render() override {
					Pointf new_point = CalculateNewPosition();
					

					sf::RectangleShape ball(sf::Vector2f(10, 10));
					
					ball.setPosition(sf::Vector2f(new_point.X-5, new_point.Y-5));
					ball.setFillColor(sf::Color::Black);

					window.draw(ball);

					sf::RectangleShape finish(sf::Vector2f(10, 10));

					finish.setPosition(sf::Vector2f(collision_point.X - 5, collision_point.Y - 5));
					finish.setFillColor(sf::Color::Red);

					window.draw(finish);
					
					//if colided
					if ( 
						(((new_point.X - collision_point.X) <= 1) && ((pos.X - collision_point.X) >= -1) && ((new_point.Y - collision_point.Y) <= 1) && ((pos.Y - collision_point.Y) >= -1)) ||
						(((new_point.X - collision_point.X) <= 1) && ((pos.X - collision_point.X) >= -1) && ((new_point.Y - collision_point.Y) >= -1) && ((pos.Y - collision_point.Y) <= 1)) ||
						(((new_point.X - collision_point.X) >= -1) && ((pos.X - collision_point.X) <= 1) && ((new_point.Y - collision_point.Y) <= 1) && ((pos.Y - collision_point.Y) >= -1)) ||
						(((new_point.X - collision_point.X) >= -1) && ((pos.X - collision_point.X) <= 1) && ((new_point.Y - collision_point.Y) >= -1) && ((pos.Y - collision_point.Y) <= 1)) ||
						( (new_point.X < 0)) ||
						((new_point.X > app_mngr.scr_width))
					) {
						if(colliding_object!=NULL)
							colliding_object->CollideWith(*this);

						manager.SetCurrentStatus( GameManager::GameStatusEnum::player_move );

						manager.RemoveComponent(identifier);

					}
					pos = new_point;

				};

				virtual void ProcessEvent(sf::Event & e) override {};
				virtual std::array<int, TanksAppManager::scr_width+1> & GetTopCollosionLine() override {
					for (auto &i : collision_arr)
						i = INT_MAX;
					return collision_arr;
				};
				Fireball(TanksAppManager & app_mngr, GameManager & game_manager, Pointf start, Pointf move_vector, std::string && identifier) :GameBaseComponent(app_mngr, game_manager), pos{ start }, move_vector{ move_vector }, identifier{ identifier } {
					InitCollisions();
					clock.restart(); 
				};

				virtual std::string Type() override {
					return "Fireball";
				}
				virtual void CollideWith(GameBaseComponent & component) override {}

			};
		}
	}
}
#endif