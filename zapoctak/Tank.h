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
#include "TankProperties.h"

namespace TanksGame {
	namespace Components {
		namespace Game {
			class Tank : public GameBaseComponent {
			private:
				TankProperties & properties;
				BasicStructres::Point position;
				int_least8_t angle = 0;
				int_least16_t canon_angle = 0;

				std::array<int, TanksAppManager::scr_width + 1> collision_line;

				void MoveLeft() {
					if (properties.fuel > 0) {
						int position_y, slope;
						Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));

						landscape.GetYAndSlopeInPoint(position.X - properties.max_speed, position_y, slope);
						angle = slope;
						position.Y = position_y;
						position.X = position.X - properties.max_speed;

						properties.fuel--;
					}
				}
				void MoveRight(){
					if (properties.fuel > 0) {
						int position_y, slope;
						Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
						landscape.GetYAndSlopeInPoint(position.X + properties.max_speed, position_y, slope);
						angle = slope;
						position.Y = position_y;
						position.X = position.X +properties.max_speed;
						properties.fuel--;
					}
				}
				
				void ChooseNextFireball() {
					auto it = properties.fireballs.find(properties.current_fireball);
					it++;
					if (it == properties.fireballs.end())
						it = properties.fireballs.begin();
					properties.current_fireball = it->first;
					properties.current_fireball_count = it->second.first;
				}
				void ChoosePrevFireball() {
					auto it = properties.fireballs.find(properties.current_fireball);
					if (it == properties.fireballs.begin())
						it = properties.fireballs.end();
					it--;
					
					properties.current_fireball = it->first;
					properties.current_fireball_count = it->second.first;
				}
				
				void Fire() {
					//if have enough ammo
					if (properties.current_fireball_count > 0) {
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

						manager.InsertComponent("fireball", std::make_unique<Components::Game::Fireball>(app_mngr, manager, canon_end, BasicStructres::Point{ (int)(sin(((canon_angle + angle)*3.14) / 180) * properties.current_strength), -(int)(cos(((canon_angle + angle)*3.14) / 180) * properties.current_strength) }, "fireball", properties.current_fireball, properties.player));
						properties.fireballs.find(properties.current_fireball)->second.first--;
						properties.current_fireball_count--;
					}
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
				

				// Inherited via BaseComponent
				virtual void Render() override {					

					sf::RectangleShape canon(sf::Vector2f(0, 0));
					canon.setSize(sf::Vector2f(6, 35));
					canon.setFillColor(BasicStructres::Color{ 0x000000 });

					window.draw(canon, getCanonTransform());

					sf::RectangleShape tank(sf::Vector2f(0, 0));
					tank.setSize(sf::Vector2f(40, 20));
					tank.setFillColor(properties.color);

					window.draw(tank, getTankTransform());

					
				};

				virtual void ProcessEvent(sf::Event & e) override {
					if ((manager.CurrentPlayer() == properties.player) && (manager.CurrentStatus() == GameManager::GameStatusEnum::player_move)) {
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
							if (properties.current_strength < properties.max_strength)
								properties.current_strength++;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
							if (properties.current_strength > 0)
								properties.current_strength--;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)) {
							ChoosePrevFireball();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::End)) {
							ChooseNextFireball();
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
				Tank(TanksAppManager & app_mngr, GameManager & game_manager, TankProperties & properties) :GameBaseComponent(app_mngr, game_manager), properties{ properties } { InitPosition(); };

				void InitPosition() {
					int position_y, slope;
					Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
					landscape.GetYAndSlopeInPoint(properties.init_x_position, position_y, slope);
					angle = slope;
					position.Y = position_y;
					position.X = properties.init_x_position;
				}

				virtual std::string Type() override {
					return "Tank";
				}
				virtual void CollideWith(GameBaseComponent * component) override {
					if (component->Type() == "Fireball") {
						Fireball * fireball = (dynamic_cast<Fireball*>(component));
						properties.health -= fireball->getDamage();
						if (properties.health <= 0) {
							manager.PlayerLost(properties.player, fireball->owner_player_id);
							InitPosition();
						}
					}
				}

			};

		}
	}
}
#endif