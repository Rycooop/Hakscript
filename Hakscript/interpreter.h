#ifndef HAKSCRIPT_INTERPRETER_H
#define HAKSCRIPT_INTERPRET_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <optional>
#include <functional>


class Interpreter {
public:
	Interpreter() = default;
	~Interpreter() = default;

	Interpreter(const std::ifstream* File);

	void Run();
	void Shutdown();

	inline std::string GetLastError() { return this->ErrorStack.back(); }

private:
	const std::ifstream* HakscriptFile;
	std::vector<std::string> ErrorStack;
};


#endif HAKSCRIPT_INTERPRETER_H