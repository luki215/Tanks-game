#pragma once
#ifndef tanks_exceptions_header
#define tanks_exceptions_header

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
			CannotInitSDLException(std::string SDL_error) : TanksException("Cannot init SDL, Error:" + SDL_error){}
	};




#endif