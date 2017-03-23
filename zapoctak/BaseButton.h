#pragma once
#pragma once
#ifndef tanks_base_button_header
#define tanks_base_button_header

#include "BaseComponent.h"
#include <SFML/Window.hpp>
#include <string>
#include "TanksAppManager.h"
#include "BasicStructures.h"
#include "Exceptions.h"
#include <functional>

namespace TanksGame {
	namespace Components {
		namespace Buttons {
			class BaseButton : public BaseComponent {
			private:
				bool isMouseInside(int x, int y) {
					//Check if mouse is in button
					bool inside = true;
					//Mouse is left of the button
					if (x < position.PosX)
					{
						inside = false;
					}
					//Mouse is right of the button
					else if (x > position.PosX + position.SizeX)
					{
						inside = false;
					}
					//Mouse above the button
					else if (y < position.PosY)
					{
						inside = false;
					}
					//Mouse below the button
					else if (y > position.PosY + position.SizeY)
					{
						inside = false;
					}

					return inside;
				}

				using Color = BasicStructres::Color;
				using SizeAndPos = BasicStructres::SizeAndPos;
			protected:
				std::string text = "Button";
				std::function<void()> action;
				SizeAndPos position = SizeAndPos{ 0,0,80,30 };
				Color background = Color{ 0xd3, 0xd3, 0xd3 };
				Color render_background = background;
				Color text_color = Color{ 0, 0, 0 };
				sf::Font font;

				virtual void OnHover(sf::Event &e) { render_background = background + 20; }
				virtual void OnMouseDown(sf::Event &e) { render_background = background - 20; }
				virtual void OnMouseUp(sf::Event &e) {
					render_background = background + 20;
					action();
				}


			public:
				virtual ~BaseButton() {	};

				virtual void ProcessEvent(sf::Event &e) override {
					//handle mouse events

					if (e.type == sf::Event::MouseMoved) {
						if (isMouseInside(e.mouseMove.x, e.mouseMove.y))
							OnHover(e);
						else
							render_background = background;
					}
					if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
						if (isMouseInside(e.mouseButton.x, e.mouseButton.y))
							OnMouseDown(e);
					}
					if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
						if (isMouseInside(e.mouseButton.x, e.mouseButton.y))
							OnMouseUp(e);
					}
				};
				virtual void Render() override {

					sf::RectangleShape rectangle(sf::Vector2f(position.SizeX, position.SizeY));
					rectangle.setPosition(sf::Vector2f(position.PosX, position.PosY));
					rectangle.setFillColor(render_background);
					sf::Text btn_text;

					// select the font
					btn_text.setFont(font);  

					btn_text.setString(text);
					btn_text.setCharacterSize(position.SizeY/2);

					btn_text.setFillColor(text_color);
					btn_text.setPosition(position.PosX + position.SizeX / 2 - btn_text.getLocalBounds().width/2, position.PosY + position.SizeY / 2 - btn_text.getLocalBounds().height/2 );
					window.draw(rectangle);
					window.draw(btn_text);


				};

				
				BaseButton(TanksAppManager & app_mngr) :BaseButton(app_mngr, []() {}, "Button", SizeAndPos{ 0, 0, 80, 30 }, Color{ 0xd3, 0xd3, 0xd3 }, Color{ 0, 0, 0 } ) {};
				BaseButton(TanksAppManager & app_mngr, std::function<void()> onclick_action, std::string text, SizeAndPos position) :BaseButton(app_mngr, onclick_action, text, position, Color{ 0xd3, 0xd3, 0xd3 }, Color{ 0, 0, 0 }) { };
				BaseButton(TanksAppManager & app_mngr, std::function<void()> onclick_action, std::string text, SizeAndPos position, Color background) :BaseButton(app_mngr, onclick_action, text, position, background, Color{ 0, 0, 0 }) { };
				BaseButton(TanksAppManager & app_mngr, std::function<void()> onclick_action, std::string text, SizeAndPos position, Color background, Color text_color) :BaseComponent(app_mngr), action{ onclick_action }, text{ text }, position{ position }, background{ background }, text_color{ text_color } {
					
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