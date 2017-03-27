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
				std::string *dynamic_text = NULL;
				int *dynamic_text_int = NULL;
				uint_least16_t *dynamic_text_uint = NULL;
				SizeAndPos position;
				Color background = Color{ 0xff, 0xff, 0xff, 0x00 };
				Color text_color = Color{ 0, 0, 0 };
				Color * dynamic_text_color = NULL;
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
					if (dynamic_text != NULL)
						btn_text.setString(*dynamic_text);
					else if (dynamic_text_int != NULL) {
						btn_text.setString(std::to_string(*dynamic_text_int));
					}
					else if (dynamic_text_uint != NULL) {
						btn_text.setString(std::to_string(*dynamic_text_uint));
					}
					else
						btn_text.setString(text);
					btn_text.setCharacterSize(position.SizeY);

					btn_text.setFillColor(text_color);
					if(dynamic_text_color!=NULL)
						btn_text.setFillColor(*dynamic_text_color);

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

				TextComponent(TanksAppManager & app_mngr, std::string *text, SizeAndPos position, Color text_color) :BaseComponent(app_mngr), dynamic_text{ text }, position{ position }, background{ BasicStructres::Color(0x00, 0x00, 0x00, 0x00) }, text_color{ text_color } {
					if (!font.loadFromFile("font.ttf"))
					{
						throw CannotLoadFontException("font.ttf");
					}
				};
				TextComponent(TanksAppManager & app_mngr, int *text, SizeAndPos position, Color text_color) :BaseComponent(app_mngr), dynamic_text_int{ text }, position{ position }, background{ BasicStructres::Color{ 0, 0, 0, 0 } }, text_color{ text_color } {
					if (!font.loadFromFile("font.ttf"))
					{
						throw CannotLoadFontException("font.ttf");
					}
				};
				TextComponent(TanksAppManager & app_mngr, uint_least16_t *text, SizeAndPos position, Color text_color) :BaseComponent(app_mngr), dynamic_text_uint{ text }, position{ position }, background{ BasicStructres::Color{0, 0, 0, 0} }, text_color{ text_color } {
					if (!font.loadFromFile("font.ttf"))
					{
						throw CannotLoadFontException("font.ttf");
					}
				};

				TextComponent(TanksAppManager & app_mngr, std::string text, SizeAndPos position, Color * text_color) :BaseComponent(app_mngr), text{ text }, position{ position }, background{ BasicStructres::Color{0x000000, 0 } }, dynamic_text_color{ text_color } {
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