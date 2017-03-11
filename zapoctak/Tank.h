#pragma once
#ifndef tanks_components_game_tank_header
#define tanks_components_game_tank_header

#include "TanksAppManager.h"
#include "Render.h"
#include <SFML/Window.hpp>
#include "GameBaseComponent.h"
#include "BasicStructures.h"
#include "GameManager.h"
#include "Landscape.h"
#include "Fireball.h"
#include <map>
namespace TanksGame {
	namespace Components {
		namespace Game {

			struct TankProperties {
				using s_uint = uint_least16_t;
				uint_least8_t player;
				s_uint max_health;
				s_uint health;
				s_uint max_fuel;
				s_uint max_speed;
				s_uint max_strength;
				BasicStructres::Color color;
				int init_x_position;
				std::map<std::string, s_uint> fireballs;

			};

			class Tank : public GameBaseComponent {
			private:
				BasicStructres::Point position;
				int_least8_t angle = 0;
				int_least16_t canon_angle = 0;
				uint_least16_t strength;
				uint_least16_t health;

				std::map<std::string, uint_least16_t> fireballs;

				std::array<int, TanksAppManager::scr_width + 1> collision_line;

				void MoveLeft() {
					int position_y, slope;
					Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
					
					landscape.GetYAndSlopeInPoint(position.X-max_speed, position_y, slope);
					angle = slope;
					position.Y = position_y;
					position.X = position.X - max_speed;
				}
				void MoveRight(){

					int position_y, slope;
					Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
					landscape.GetYAndSlopeInPoint(position.X + max_speed, position_y, slope);
					angle = slope;
					position.Y = position_y;
					position.X = position.X + max_speed;
				}
				void Fire() {
					manager.SetCurrentStatus(GameManager::GameStatusEnum::shot);
					//count end point of canon
					sf::Transform canon_transform;
					canon_transform.translate(sf::Vector2f(position.X, position.Y - 10));
					sf::Transform rotation;
					rotation.rotate(angle, sf::Vector2f(0, 10));
					sf::Vector2f positionAfterRotation = rotation.transformPoint(sf::Vector2f(0, 10));
					canon_transform.rotate(angle, positionAfterRotation);
					canon_transform.rotate(canon_angle, sf::Vector2f(0, -10));

					sf::Vector2f canon_end = canon_transform.transformPoint(sf::Vector2f{ 0, -40 });
					
					manager.InsertComponent("fireball", std::make_unique<Components::Game::Fireball>(app_mngr, manager, canon_end , BasicStructres::Point{(int)(sin(((canon_angle+angle)*3.14)/180) * strength), -(int)(cos(((canon_angle + angle)*3.14) / 180) * strength )}, "fireball"));
				}

				sf::Transform getCanonTransform() {
					sf::Transform canon_transform;
					canon_transform.translate(sf::Vector2f(position.X - 3, position.Y - 45));
					sf::Transform rotation;
					rotation.rotate(angle, sf::Vector2f(3, 45));
					sf::Vector2f positionAfterRotation_1 = rotation.transformPoint(sf::Vector2f(3, 45));
					canon_transform.rotate(angle, positionAfterRotation_1);
					canon_transform.rotate(canon_angle, sf::Vector2f(3, 25));
					return canon_transform;
				}
				sf::Transform getTankTransform() {
					sf::Transform tank_transform;
					tank_transform.translate(sf::Vector2f(position.X - 20, position.Y - 20));
					tank_transform.rotate(angle, sf::Vector2f(20, 20));
					return tank_transform;
				}

				void recalculateCollisionLine(std::array<sf::Vector2f, 4> & point_array) {
					auto point_before = *(point_array.end() - 1);
					for (auto point : point_array) {
						bool switched = false;
						if (point_before.x > point.x) {
							auto a = point_before;
							point_before = point;
							point = a;
							switched = true;
						}
						double angle_rad = 0;
						if (point.x - point_before.x != 0)
							angle_rad = atan((double)(point.y - point_before.y) / (point.x - point_before.x));

						for (auto i = point_before.x; i <= point.x; i++) {
							auto y = (tan(angle_rad) * (i - point_before.x)) + point_before.y;
							if (collision_line[i] > y)
								collision_line[i] = y;
						}
						point_before = switched? point_before : point;
					}
				}

			public:
				using s_uint = uint_least16_t;
				s_uint max_health;
				s_uint max_fuel;
				s_uint max_speed;
				s_uint max_strength;
				uint_least8_t player;
				BasicStructres::Color color;
				

				// Inherited via BaseComponent
				virtual void Render() override {					

					sf::RectangleShape tank(sf::Vector2f(0, 0));
					tank.setSize(sf::Vector2f(40, 20));
					tank.setFillColor(color);

					window.draw(tank, getTankTransform());

					sf::RectangleShape canon(sf::Vector2f(0, 0));
					canon.setSize(sf::Vector2f(6, 35));
					canon.setFillColor(color);

					window.draw(canon, getCanonTransform());
					
				};

				virtual void ProcessEvent(sf::Event & e) override {
					if ((manager.CurrentPlayer() == player) && (manager.CurrentStatus() == GameManager::GameStatusEnum::player_move)) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
							if (canon_angle >= -88)
								canon_angle -= 2;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
							if (canon_angle <= 88)
								canon_angle += 2;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
							MoveLeft();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
							MoveRight();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
							Fire();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
							if (strength < max_strength)
								strength++;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
							if (strength > 0)
								strength--;
						}
					}
				};

				virtual std::array<int, TanksAppManager::scr_width+1> & GetTopCollosionLine() override {
					for (auto &i : collision_line)
						i = INT_MAX;


					/////// points to compute tank collision area from
					/*
						points like:
			   
						    c0 - c1
							 \   \
							  \   \
						t1 - - \   \ - - t2
						|	   c3 - c2    |
						t0 - - - - - - - t3
					
					*/

					std::array<sf::Vector2f, 4> tank_border_points{};
					std::array<sf::Vector2f, 4> canon_border_points{};

					auto tank_transform = getTankTransform();
					auto canon_transform = getCanonTransform();
					tank_border_points[0] = tank_transform.transformPoint(sf::Vector2f{ 0, 20 });
					tank_border_points[1] = tank_transform.transformPoint(sf::Vector2f{ 0, 0 });
					tank_border_points[2] = tank_transform.transformPoint(sf::Vector2f{ 40, 0 });
					tank_border_points[3] = tank_transform.transformPoint(sf::Vector2f{ 40, 20 });
					canon_border_points[0] = canon_transform.transformPoint(sf::Vector2f{ 0, 0 });
					canon_border_points[1] = canon_transform.transformPoint(sf::Vector2f{ 6, 0 });
					canon_border_points[2] = canon_transform.transformPoint(sf::Vector2f{ 0, 35 });
					canon_border_points[3] = canon_transform.transformPoint(sf::Vector2f{ 6, 35 });



					recalculateCollisionLine(tank_border_points);
					recalculateCollisionLine(canon_border_points);
					

					return  collision_line;
				};
				Tank(TanksAppManager & app_mngr, GameManager & game_manager, TankProperties properties) :GameBaseComponent(app_mngr, game_manager),
					max_fuel{ properties.max_fuel },
					max_health{ properties.max_health },
					health{ properties.health },
					max_speed{ properties.max_speed },
					max_strength{ properties.max_strength },
					strength{ (uint_least16_t) (properties.max_strength / 2)},
					player{ properties.player },
					color{ properties.color },
					fireballs{ properties.fireballs }					
					{	int position_y, slope;
						Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
						landscape.GetYAndSlopeInPoint(properties.init_x_position, position_y, slope);
						angle = slope;
						position.Y = position_y;
						position.X = properties.init_x_position;
				};

				virtual std::string Type() override {
					return "Tank";
				}
				virtual void CollideWith(GameBaseComponent & component) override {
					if (component.Type() == "Fireball")
						std::cout << "Destroyed!";
				}

			};

		}
	}
}
#endif