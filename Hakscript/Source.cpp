#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <string>

#include "interpreter.h"


int main(int argc, char** argv) {
	std::ifstream FileStream;

	if (argc > 1) 
		FileStream.open(argv[1]);
	else {
		std::cerr << "[-] No file passed as argument..." << std::endl;
		Sleep(3000);
		return 0;
	}

	Interpreter interpreter(&FileStream);
	
	interpreter.Run();
	interpreter.Shutdown();

	Sleep(4000);
}