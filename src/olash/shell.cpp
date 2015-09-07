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
	std::string input("i32 add(i32 x, i32 y) { return x + y; }");
	//input += getchar();
	//std::cin >> input;
	return input;
}

void Shell::executeCode(std::string code)
{
	_compiler.feed(code);
}

}