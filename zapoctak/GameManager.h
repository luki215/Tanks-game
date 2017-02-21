#pragma once
#pragma once
#ifndef game_manager_header
#define game_manager_header
namespace TanksGame {
	class GameManager {
	private:
		using components_map = std::map<std::string, std::unique_ptr<Components::BaseComponent>>;
		components_map components;
	public:
		void InsertComponent(std::string identifier, std::unique_ptr<Components::BaseComponent> component){
			components.emplace(identifier, std::move(component));
		}
		Components::BaseComponent & GetComponent(std::string identifier) {
			return *(components.find(identifier)->second);
		}
		const components_map & GetComponents() const {
			return components;
		}
	};
}

#endif