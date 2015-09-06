#include "shell.h"
#include <iostream>
#include <stdio.h>

namespace olash {

Shell::Shell():
	_shouldStop(false)
{

}

Shell::~Shell()
{

}

int Shell::enter()
{
	//while (!_shouldStop) {
	std::cout << "running code: " << getInput() << "\n";
	executeCode(getInput());
	//}
}

void Shell::scheduleExit()
{
	_shouldStop = true;
}

std::string Shell::getInput()
{
	std::string input("1 -2.501 -3 50 function + function=function -10 shitfunction functionlol a");
	//input += getchar();
	//std::cin >> input;
	return input;
}

void Shell::executeCode(std::string code)
{
	_compiler.feed(code);
}

}