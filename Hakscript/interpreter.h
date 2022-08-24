#ifndef HAKSCRIPT_INTERPRETER_H
#define HAKSCRIPT_INTERPRET_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>


class Interpreter {
public:
	Interpreter() = default;
	~Interpreter() = default;

	Interpreter(std::ifstream* File);

	void Run();
	void Shutdown();

	inline std::string GetLastError() { return this->ConsoleStack.back(); }

private:
	bool Interpret(const std::string& line);
	void HandleSetup(const std::string& Arg);

	std::ifstream* HakscriptFile;
	std::vector<std::string> ConsoleStack;
	std::uint16_t LineCount = 0;
	bool IsInSetup = true, IsConsoleMode = false;
};


#endif HAKSCRIPT_INTERPRETER_H