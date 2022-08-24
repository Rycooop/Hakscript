#ifndef HAKSCRIPT_INTERPRETER_H
#define HAKSCRIPT_INTERPRET_H

#include <iostream>
#include <fstream>


class Interpreter {
public:
	Interpreter() = default;

	Interpreter(const std::ifstream* File);

};


#endif HAKSCRIPT_INTERPRETER_H