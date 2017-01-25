#include <iostream>
#include <chrono>
#include <ctime>
#include "Render.h"
#include <fstream>


int main(int argc, char ** argv) {

	try {
		std::ofstream debug_log{ "info.log" };
		
		try {

			Render render;
			render.Init();

			render.Destroy();




		}
		catch (TanksException &e) {
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