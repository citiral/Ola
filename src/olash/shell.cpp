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
	//std::cout << "running code: " << getInput() << "\n";

	executeCode(getInput());
	return 0;
	//}
}

void Shell::scheduleExit()
{
	_shouldStop = true;
}

std::string Shell::getInput()
{
	/*std::string input("\nfunction add(i32 x, i32 y) -> i32 {\n"
							  "\t1+2+3\n"
							  "}\n"
			                  "function main() -> i32\n"
			                  "{\n"
			                  "\tadd(2+5+70,2*3+4*5)\n"
			                  "}");*/
	//input += getchar();
	//std::cin >> input;
	std::string input;
	std::cin >> input;
	return input;
}

void Shell::executeCode(std::string code)
{
	_compiler.feed(code);
}

}