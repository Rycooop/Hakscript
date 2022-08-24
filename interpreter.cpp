#include "interpreter.h"


Interpreter::Interpreter(const std::ifstream * File) {
	this->HakscriptFile = File;
	this->ErrorStack.push_back("");
}

void Interpreter::Run() {
	if (!this->HakscriptFile) {
		this->ErrorStack.push_back("[-] Did not pass a valid Hakscript file");
		return;
	}


}

void Interpreter::Shutdown() {

}