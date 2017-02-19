#pragma once
#pragma once
#ifndef tanks_base_button_header
#define tanks_base_button_header

#include "BaseComponent.h";
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "TanksGameManager.h"
#include "BasicStructures.h"

namespace TanksGame {
	namespace Components {
		namespace Buttons {
			class BaseButton : public BaseComponent {
				using Color = BasicStructres::Color;
				using SizeAndPos = BasicStructres::SizeAndPos;
			protected:
				std::string text = "Button";
				GameStatusEnum action = GameStatusEnum::invalid;
				SizeAndPos position = SizeAndPos{0,0,80,30};
				Color background = Color{ 0xd3, 0xd3, 0xd3 };
				Color render_background = background;
				Color text_color = Color{ 0, 0, 0 };
				TTF_Font* font = NULL;

			public:
				virtual ~BaseButton() {	TTF_CloseFont(font); };
			
				virtual void OnHover(SDL_Event &e) { render_background = background +20; }
				virtual void OnMouseDown(SDL_Event &e) { render_background = background -  20; }
				virtual void OnMouseUp(SDL_Event &e){
					render_background = background+20;
					game_mngr.SwitchGameStatusTo(action);
				}
				virtual void ProcessEvent(SDL_Event &e) override{
					//handle mouse events
					if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
					{
						//Get mouse position
						int x, y;
						SDL_GetMouseState(&x, &y);
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
						//Mouse is outside button
						if (!inside)
						{
							render_background = background;
						}
						//Mouse is inside button
						else
						{
							//Set mouse over sprite
							switch (e.type)
							{
							case SDL_MOUSEMOTION:
								OnHover(e);
								break;

							case SDL_MOUSEBUTTONDOWN:
								OnMouseDown(e);
								break;

							case SDL_MOUSEBUTTONUP:
								OnMouseUp(e);
								break;
							}
						}
					}
				};
				virtual void Render() override {
					SDL_Rect fillRect = { position.PosX, position.PosY, position.SizeX, position.SizeY };
					SDL_SetRenderDrawColor(renderer, render_background.R, render_background.G, render_background.B, render_background.A);
					SDL_RenderFillRect(renderer, &fillRect);
					
					SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), text_color);
					SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
				
					SDL_Rect Message_rect; //create a rect
					Message_rect.x = position.PosX+ position.SizeX/2 - surfaceMessage->w/2;   
					Message_rect.y = position.PosY + position.SizeY / 2- surfaceMessage->h/2;
					Message_rect.w = surfaceMessage->w; 
					Message_rect.h = surfaceMessage->h; 

					SDL_RenderCopy(renderer, Message, NULL , &Message_rect); 
				
					SDL_FreeSurface(surfaceMessage);
					SDL_DestroyTexture(Message);


				};

				BaseButton(TanksGameManager & game_mngr) :BaseComponent(game_mngr){font = TTF_OpenFont("font.ttf", position.SizeY*0.5);};
				BaseButton(TanksGameManager & game_mngr, std::string text) :BaseComponent(game_mngr), text{text}{};
				BaseButton(TanksGameManager & game_mngr, std::string text, Color background) :BaseComponent(game_mngr), text{ text }, background{ background } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, std::string text, SizeAndPos position) :BaseComponent(game_mngr), text{ text }, position{ position } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, std::string text, SizeAndPos position, Color background) :BaseComponent(game_mngr), text{ text }, position{ position }, background{ background } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, std::string text, SizeAndPos position, Color background, Color text_color) :BaseComponent(game_mngr), text{ text }, position{ position }, background { background }, text_color{ text_color } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, GameStatusEnum action) :BaseComponent(game_mngr), action{ action } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, GameStatusEnum action, std::string text) :BaseComponent(game_mngr), action{ action }, text{ text } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, GameStatusEnum action, std::string text, Color background) :BaseComponent(game_mngr), action{ action }, text{ text }, background{ background } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, GameStatusEnum action, std::string text, SizeAndPos position) :BaseComponent(game_mngr), action{ action }, text{ text }, position{ position } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, GameStatusEnum action, std::string text, SizeAndPos position, Color background) :BaseComponent(game_mngr), action{ action }, text{ text }, position{ position }, background{ background } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };
				BaseButton(TanksGameManager & game_mngr, GameStatusEnum action, std::string text, SizeAndPos position, Color background, Color text_color) :BaseComponent(game_mngr), action{ action }, text{ text }, position{ position }, background{ background }, text_color{ text_color } { font = TTF_OpenFont("font.ttf", position.SizeY*0.5); };


			};
		}
	}
}

#endif