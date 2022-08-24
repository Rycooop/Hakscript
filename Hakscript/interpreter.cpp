#include "interpreter.h"


Interpreter::Interpreter(std::ifstream* File) {
	this->HakscriptFile = File;
	this->ConsoleStack.push_back("[-] Invalid Syntax");
}

void Interpreter::Run() {
	if (!this->HakscriptFile) {
		this->ConsoleStack.push_back("[-] Did not pass a valid Hakscript file");
		return;
	}

	std::string currLine;
	while (std::getline(*this->HakscriptFile, currLine)) {
		if (this->IsInSetup)
			this->HandleSetup(currLine);
		else {
			if (!this->Interpret(currLine))
				break;
		}
	}

}

void Interpreter::Shutdown() {
	std::cout << this->GetLastError() << std::endl;
}

bool Interpreter::Interpret(const std::string& line) {
	if (line.find("Hakscript.End:") != std::string::npos) {
		this->ConsoleStack.push_back("[+] Script Finished Executing...");
		return false;
	}

	std::size_t pos = line.find("Print");
	if (pos != std::string::npos) {
		if (this->IsConsoleMode) {
			std::string Message(line.substr(pos));
			std::cout << "[Print Message] " << Message << std::endl;
		}
	}

	return true;
}

void Interpreter::HandleSetup(const std::string& Arg) {
	if (Arg.find("Hakscript.Begin:") != std::string::npos) {
		this->IsInSetup = false;
		return;
	}

	if (Arg.find("Hakscript.Print") != std::string::npos) {
		this->IsConsoleMode = true;
	}
}