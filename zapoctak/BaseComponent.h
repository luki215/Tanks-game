#pragma once
#ifndef tanks_base_component_header
#define tanks_base_component_header


#include <SFML/Window.hpp>
#include "GameScreenable.h"

namespace TanksGame {
	namespace Components {

		class BaseComponent {
		protected:
			TanksAppManager & app_mngr;
			sf::RenderWindow & window;
		public:
			virtual ~BaseComponent() {};
			virtual void Render() = 0;
			virtual void ProcessEvent(sf::Event &e) = 0;
			BaseComponent(TanksAppManager & app_mngr) :app_mngr{ app_mngr }, window{ app_mngr.GetWindow() }{};
		};

	}
}

#endif