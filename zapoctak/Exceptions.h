#pragma once
#ifndef tanks_exceptions_header
#define tanks_exceptions_header
namespace TanksGame {
	class TanksException {
	protected:
		std::string msg;


	public:
		TanksException(std::string message) : msg{ message } {}
		virtual std::string what() {
			return msg;
		}
	};


	class CannotInitSDLException : public TanksException {
	public:
		CannotInitSDLException(std::string SDL_error) : TanksException("Cannot init SDL, Error:" + SDL_error) {}
	};
	class TooFewGroundPointsException : public TanksException {
	public:
		TooFewGroundPointsException() : TanksException("Too few point to make ground. You need at least 2") {}
	};
	class CannotLoadFontException : public TanksException {
	public:
		CannotLoadFontException(std::string font) : TanksException("Cannot load font: "+ font) {}
	};
}



#endif