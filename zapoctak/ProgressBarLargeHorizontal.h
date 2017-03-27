#pragma once
#ifndef tanks_components_progressbar_horizontal_header
#define tanks_components_progressbar_horizontal_header

#include <SFML/Window.hpp>
#include "GameBaseComponent.h"
#include <vector>
#include "BasicStructures.h"
#include "TanksAppManager.h"
#include "Exceptions.h"

namespace TanksGame {
	namespace Components {
		namespace Others {

			class ProgressBarLargeHorizontal : public BaseComponent {
			private:

				using Color = BasicStructres::Color;
				using SizeAndPos = BasicStructres::SizeAndPos;
				SizeAndPos position;
				uint_least16_t & value;
				uint_least16_t & max_value;
				Color background = Color{ 0xff, 0xff, 0xff, 0x00 };

			public:

				virtual void ProcessEvent(sf::Event &e) override {

				};
				virtual void Render() override {

					sf::RectangleShape border(sf::Vector2f(position.SizeX, position.SizeY));
					border.setPosition(sf::Vector2f(position.PosX, position.PosY));
					border.setFillColor(BasicStructres::Color{0x000000});
				
					sf::RectangleShape inside(sf::Vector2f(position.SizeX - 4, position.SizeY - 4));
					inside.setPosition(sf::Vector2f(position.PosX + 2, position.PosY + 2));
					inside.setFillColor(BasicStructres::Color{ 0xffffff });

					sf::RectangleShape progress(sf::Vector2f((position.SizeX - 4)*value /100, (position.SizeY - 4)));
					progress.setPosition(sf::Vector2f(position.PosX + 2, position.PosY + 2));
					progress.setFillColor(background);

						
					window.draw(border);
					window.draw(inside);
					window.draw(progress);


				};

				void SetValue(int_least8_t value) {
					this->value = value;
				}

				ProgressBarLargeHorizontal(TanksAppManager & app_mngr, SizeAndPos position, Color background, uint_least16_t& value, uint_least16_t & max_value) :BaseComponent(app_mngr), position{ position }, background{ background }, value{ value }, max_value{ max_value } {};


			};
		}
	}
}
#endif