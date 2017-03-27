#pragma once
#ifndef tanks_components_progressbar_vertical_header
#define tanks_components_progressbar_vertical_header

#include <SFML/Window.hpp>
#include "GameBaseComponent.h"
#include <vector>
#include "BasicStructures.h"
#include "TanksAppManager.h"
#include "Exceptions.h"

namespace TanksGame {
	namespace Components {
		namespace Others {

			class ProgressBarVertical : public BaseComponent {
			private:

				using Color = BasicStructres::Color;
				using SizeAndPos = BasicStructres::SizeAndPos;
				SizeAndPos position;
				uint_least16_t & value;
				uint_least16_t & base;
				Color background = Color{ 0xff, 0xff, 0xff, 0x00 };

			public:

				virtual void ProcessEvent(sf::Event &e) override {

				};
				virtual void Render() override {

					sf::RectangleShape border(sf::Vector2f(position.SizeX, position.SizeY));
					border.setPosition(sf::Vector2f(position.PosX, position.PosY));
					border.setFillColor(BasicStructres::Color{ 0x000000 });

					sf::RectangleShape inside(sf::Vector2f(position.SizeX - 4, position.SizeY - 4));
					inside.setPosition(sf::Vector2f(position.PosX + 2, position.PosY + 2));
					inside.setFillColor(BasicStructres::Color{ 0xffffff });

					sf::RectangleShape progress(sf::Vector2f((position.SizeX - 4), (position.SizeY-4)*value / base));
					progress.setPosition(sf::Vector2f(position.PosX + 2, position.PosY - 2 + position.SizeY - (position.SizeY - 4)*value / base));
					progress.setFillColor(background);


					window.draw(border);
					window.draw(inside);
					window.draw(progress);


				};

				void SetValue(int_least8_t value) {
					this->value = value;
				}

				ProgressBarVertical(TanksAppManager & app_mngr, SizeAndPos position, Color background, uint_least16_t & value, uint_least16_t & base) :BaseComponent(app_mngr), position{ position }, background{ background }, value{ value }, base{ base } {};


			};
		}
	}
}
#endif