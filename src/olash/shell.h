#pragma once
#include <string>
#include "ola.h"

namespace olash {

class Shell {
public:
	Shell();
	~Shell();

	//runs the shell untill it terminates, either gracefull, returning 0, or with an error, returning the errorcode
	int enter();
	void scheduleExit();

private:
	std::string getInput();

	//is put on true if the shell needs to exit
	bool _shouldStop;

	//the compiler the Shell uses
	ola::OlaToLlvmCompiler _compiler;
};

}