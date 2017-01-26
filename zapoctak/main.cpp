#include <iostream>
#include "TanksGameManager.h"
#include "Exceptions.h"
#include <fstream>

#include<vector>

int main(int argc, char ** argv) {




	try {
		std::ofstream debug_log{ "errors.log" };
		
		try {

			
			TanksGame::TanksGameManager game;
			game.Run();



		}
		catch (TanksGame::TanksException &e) {
			debug_log << e.what().c_str() << std::endl;
		}
		catch (std::exception &e) {
			debug_log << e.what() << std::endl;
		}
		catch (...) {
			debug_log << "Undefined error" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Error in opening log file";
		throw;
	}

	return 0;
}