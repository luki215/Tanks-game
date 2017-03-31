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

			class Fireball : public GameBaseComponent {
				using Pointf = BasicStructres::Pointf;
			private:
				Pointf pos;
				Pointf move_vector;
				sf::Time last_calculated_position_time;
				double weight = 10; 
				int damage;
				int current_iteration = 0;
				int crash_iteration;
				std::array<int, TanksAppManager::scr_width + 1> collision_arr;
				Pointf collision_point;
				GameBaseComponent * colliding_object = NULL;
				std::string identifier;
				std::unique_ptr<sf::Shape> shape;
				Pointf CalculateNewPosition() {

					float v_x = move_vector.X/10;
					float v_y = move_vector.Y/10;

					Pointf new_pos;
					new_pos.X = pos.X + v_x;
					new_pos.Y = pos.Y + v_y;

					move_vector.Y += (manager.env.gravity * weight)/500;
					move_vector.Y *= manager.env.resistance;
					move_vector.X *= manager.env.resistance;


					return new_pos;
				}
				void InitCollisions(){
					auto enviroment_collision_line = manager.GetCollisionLine();
					auto move_vector_backup = move_vector;
					auto pos_backup = pos;
					auto pos_before = Pointf(pos);
					int number_of_iterations = 0;
					while (true) {
						pos = CalculateNewPosition();
						number_of_iterations++;
						if (pos.Y > TanksAppManager::scr_height || pos.X < 0 || pos.X > TanksAppManager::scr_width) {
							collision_point = Pointf( (pos.X<0)? -1 : 1, 0);
							colliding_object = NULL;
							break;
						}
						bool switched = false;
						if (enviroment_collision_line[pos.X].first <= pos.Y) {
							//Calculate exact point of collision - count line between pos_before and pos and then compare point by point with enviroment_collisoin_line
					
							if (pos_before.X > pos.X) {
								auto a = pos_before;
								pos_before = pos;
								pos = a;
								switched = true;
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
						
						
						pos_before = (switched)? pos_before : pos;
					}
					break_while:
					pos = pos_backup;
					move_vector = move_vector_backup;
					crash_iteration = number_of_iterations+1;
				}
			public:
				int owner_player_id;
				// Inherited via GameBaseComponent
				virtual void Render() override {
					Pointf new_point = CalculateNewPosition();
					current_iteration++;

					(*shape).setPosition(sf::Vector2f(new_point.X - shape->getLocalBounds().width/2, new_point.Y - shape->getLocalBounds().height / 2));
					window.draw(*shape);
					
					//if colided
					if ( current_iteration == crash_iteration) {
						if(colliding_object!=NULL)
							colliding_object->CollideWith(this);

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
				Fireball(TanksAppManager & app_mngr, GameManager & game_manager, Pointf start, Pointf move_vector, std::string && identifier, std::string spiece, int owner_player_id) :GameBaseComponent(app_mngr, game_manager), pos{ start }, move_vector{ move_vector }, identifier{ identifier }, owner_player_id{ owner_player_id } {

					if (spiece == "small-missile") {
						damage = 15;
						weight = 10;
						sf::RectangleShape ball(sf::Vector2f(5, 10));
						ball.setFillColor(sf::Color::Black);
						shape = std::make_unique<sf::RectangleShape>(std::move(ball));
					}
					else if (spiece == "large-missile") {
						damage = 25;
						weight = 20;
						sf::RectangleShape ball(sf::Vector2f(10, 20));
						ball.setFillColor(sf::Color::Black);
						shape = std::make_unique<sf::RectangleShape>(std::move(ball));
					}
					else if (spiece == "atom-bomb") {
						damage = 50;
						weight = 30;
						sf::CircleShape ball(10);
						ball.setFillColor(sf::Color::Red);
						shape = std::make_unique<sf::CircleShape>(std::move(ball));
					}
					else if (spiece == "nitrogen-bomb") {
						damage = 100;
						weight = 40;
						sf::CircleShape ball(15);
						ball.setFillColor(sf::Color::Red);
						shape = std::make_unique<sf::CircleShape>(std::move(ball));
					}
					InitCollisions();

				}

				int & getDamage() {
					return damage;
				}
				virtual std::string Type() override {
					return "Fireball";
				}
				virtual void CollideWith(GameBaseComponent * component) override {}

			};
		}
	}
}
#endif