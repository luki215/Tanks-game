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
namespace TanksGame {
	namespace Components {
		namespace Game {

			class Tank : public GameBaseComponent {
			private:
				BasicStructres::Point position{ 40, 850 };
				int_least8_t angle = 0;
				int_least8_t canon_angle = 0;
				uint_least8_t speed = 2;
			


				void MoveLeft() {
					int position_y, slope;
					Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
					
					landscape.GetYAndSlopeInPoint(position.X-speed, position_y, slope);
					angle = slope;
					position.Y = position_y;
					position.X = position.X - speed;
				}
				void MoveRight(){

					int position_y, slope;
					Landscape & landscape = dynamic_cast<Landscape &>(manager.GetComponent("landscape"));
					landscape.GetYAndSlopeInPoint(position.X + speed, position_y, slope);
					angle = slope;
					position.Y = position_y;
					position.X = position.X + speed;
				}
				void Fire() {
					//manager.InsertComponent("fireball")
				}

			public:
				using s_uint = uint_least16_t;
				s_uint health;
				s_uint max_fuel;
				s_uint max_speed;
				s_uint max_hill_slope;
				BasicStructres::Color color{ 0x000000 };



				// Inherited via BaseComponent
				virtual void Render() override {
					

					sf::RectangleShape tank(sf::Vector2f(0, 0));
					tank.setSize(sf::Vector2f(40, 20));
					tank.setFillColor(color);
					tank.setOrigin(20, 20);

					tank.setPosition(position.X, position.Y);
					tank.setRotation(angle);
					window.draw(tank);

					sf::RectangleShape canon(sf::Vector2f(0, 0));
					canon.setSize(sf::Vector2f(6, 35));
					canon.setFillColor(color);

					sf::Transform canon_transform;
					canon.setOrigin(3, 35);
					canon_transform.translate(sf::Vector2f(position.X, position.Y - 10));
				
					sf::Transform rotation;
					rotation.rotate(angle, sf::Vector2f(0, 10));
					sf::Vector2f positionAfterRotation = rotation.transformPoint(sf::Vector2f(0, 10));
					canon_transform.rotate(angle, positionAfterRotation);


					canon_transform.rotate(canon_angle, sf::Vector2f(0, -10));
				
					window.draw(canon, canon_transform);
				};

				virtual void ProcessEvent(sf::Event & e) override {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						canon_angle-=2;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						canon_angle+=2;
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
				};
				Tank(TanksAppManager & app_mngr, GameManager & game_manager ) :GameBaseComponent(app_mngr, game_manager) { };

			};

		}
	}
}
#endif