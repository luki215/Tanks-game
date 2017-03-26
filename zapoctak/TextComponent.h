#pragma once
#ifndef tanks_components_others_text_header
#define tanks_components_others_text_header

#include <SFML/Window.hpp>
#include "GameBaseComponent.h"
#include <vector>
#include "BasicStructures.h"
#include "TanksAppManager.h"
#include "Exceptions.h"

namespace TanksGame {
	namespace Components {
		namespace Others {

			class TextComponent : public BaseComponent {
			private:

				using Color = BasicStructres::Color;
				using SizeAndPos = BasicStructres::SizeAndPos;
				std::string text;
				SizeAndPos position;
				Color background = Color{ 0xff, 0xff, 0xff, 0x00 };
				Color text_color = Color{ 0, 0, 0 };
				sf::Font font;


			public:
				
				virtual void ProcessEvent(sf::Event &e) override {
					
				};
				virtual void Render() override {

					sf::RectangleShape rectangle(sf::Vector2f(position.SizeX, position.SizeY));
					rectangle.setPosition(sf::Vector2f(position.PosX, position.PosY));
					rectangle.setFillColor(background);
					sf::Text btn_text;

					// select the font
					btn_text.setFont(font);

					btn_text.setString(text);
					btn_text.setCharacterSize(position.SizeY);

					btn_text.setFillColor(text_color);
					btn_text.setPosition(position.PosX, position.PosY);
					window.draw(rectangle);
					window.draw(btn_text);


				};

				void ChangeTextColor(Color color) {
					text_color = color;
				}

				TextComponent(TanksAppManager & app_mngr, std::string text, SizeAndPos position, Color text_color) :TextComponent(app_mngr, text, position, text_color, BasicStructres::Color(0x00, 0x00, 0x00, 0x00)) {};
				TextComponent(TanksAppManager & app_mngr, std::string text, SizeAndPos position, Color text_color, Color background) :BaseComponent(app_mngr), text{ text }, position{ position }, background{ background }, text_color{ text_color } {

					if (!font.loadFromFile("font.ttf"))
					{
						throw CannotLoadFontException("font.ttf");
					}
				};


			};
		}
	}
}
#endif