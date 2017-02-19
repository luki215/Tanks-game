#pragma once
#ifndef tanks_components_game_tank_header
#define tanks_components_game_tank_header

#include "TanksGameManager.h"
#include "Render.h"
#include "SDL.h"
#include "BaseComponent.h"
#include "BasicStructures.h"
namespace TanksGame {
	namespace Components {
		namespace Game {

			class Tank : public BaseComponent {
			private:
				BasicStructres::Point position{ 40, 850 };

				int_least8_t angle = -30;
				int_least8_t canon_angle = 20;
				BasicStructres::Color color{0x000000};

			public:
				using s_uint = uint_least16_t;
				s_uint health;
				s_uint max_fuel;
				s_uint max_speed;
				s_uint max_hill_slope;




				// Inherited via BaseComponent
				virtual void Render() override {

					SDL_Texture * target_before = SDL_GetRenderTarget(renderer);

					SDL_SetRenderTarget(renderer, NULL);
					SDL_Texture * tank_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
					SDL_SetTextureBlendMode(tank_texture, SDL_BlendMode::SDL_BLENDMODE_BLEND);
					SDL_Texture * canon_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 6, 30);
					SDL_SetRenderDrawColor(renderer, color.R, color.B, color.G, color.A);

					//create canon
					SDL_SetRenderTarget(renderer, canon_texture);
					SDL_RenderFillRect(renderer, NULL);
					

					//render canon to tank
					SDL_SetRenderTarget(renderer, tank_texture);
					SDL_Rect destination = { 22, 0, 6, 30 };
					SDL_Point rot_center{ 3, 20 };
					//SDL_RenderCopy(renderer, canon_texture, NULL, &destination);
					SDL_RenderCopyEx(renderer, canon_texture, NULL, &destination, canon_angle, &rot_center, SDL_FLIP_NONE);

					//create tank					
					SDL_Rect tank = { 5, 30, 40, 20 };
					SDL_RenderFillRect(renderer, &tank);

					
					//render to image
					destination = SDL_Rect{ position.X - 20, position.Y - 50, 50, 50 };
					rot_center = SDL_Point{ 25, 50 };
					SDL_SetRenderTarget(renderer, target_before);
					//SDL_RenderCopy(renderer, tank_texture, NULL, &destination);
					SDL_RenderCopyEx(renderer, tank_texture, NULL, &destination, angle, &rot_center, SDL_FLIP_NONE);

					SDL_DestroyTexture(canon_texture);
					SDL_DestroyTexture(tank_texture);


/*

	*/			};

				virtual void ProcessEvent(SDL_Event & e) override {
				};
				Tank(TanksGameManager & game_mngr) :BaseComponent(game_mngr) { };

			};

		}
	}
}
#endif