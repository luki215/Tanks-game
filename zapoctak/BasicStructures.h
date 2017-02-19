#pragma once
#ifndef tanks_basic_structures_header
#define tanks_basic_structures_header

#include "SDL.h"
namespace TanksGame {
	namespace BasicStructres {

		struct Color {
			uint_least8_t R, G, B, A;
		public:
			Color(uint_least8_t R, uint_least8_t G, uint_least8_t B, uint_least8_t A) : R{ R }, G{ G }, B{ B }, A{ A } {};
			Color(uint_least8_t R, uint_least8_t G, uint_least8_t B) : R{ R }, G{ G }, B{ B }, A{ 0xff } {};
			Color() : R{ 0x00 }, G{ 0x00 }, B{ 0x00 }, A{ 0xff } {};
			Color(uint_least32_t hex) {
				R = static_cast<uint_least8_t>((hex & 0x00ff0000) >> 16);
				G = static_cast<uint_least8_t>((hex & 0x0000ff00) >> 8);
				B = static_cast<uint_least8_t>(hex & 0x000000ff);
				A = 0xff;
			}
			Color(uint_least32_t hex, uint_least8_t alpha) {
				R = static_cast<uint_least8_t>((hex & 0x00ff0000) >> 16);
				G = static_cast<uint_least8_t>((hex & 0x0000ff00) >> 8);
				B = static_cast<uint_least8_t>(hex & 0x000000ff);
				A = alpha;
			}
			operator SDL_Color() const { return SDL_Color{ R, G, B, A }; }
			friend Color operator+(Color left, const uint_least8_t right) { (left.R > 255 - right) ? left.R = 255 : left.R += right;
																			(left.G > 255 - right) ? left.G = 255 : left.G += right;
																			(left.B > 255 - left.B) ? left.B = 255 : left.B += right; return left; }
			friend Color operator-(Color left, const uint_least8_t right) { (right <= left.R) ? left.R -= right : left.R = 0; ; (right <= left.G)? left.G -= right : left.G = 0; (right <= left.B)?left.B -= right : left.B = 0; return left; }
		};

		struct Point {
			int X, Y;
		};

		struct SizeAndPos {
			int PosX, PosY, SizeX, SizeY;
		public:
			SizeAndPos(int PosX, int PosY, int SizeX, int SizeY) : PosX{ PosX }, PosY{ PosY }, SizeX{ SizeX }, SizeY{ SizeY } {};
			SizeAndPos() : PosX{ 0 }, PosY{ 0 }, SizeX{ 0 }, SizeY{ 0 } {};
		};
	}

}

#endif