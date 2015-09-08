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
	return 0;
	//}
}

void Shell::scheduleExit()
{
	_shouldStop = true;
}

std::string Shell::getInput()
{
	std::string input("function add(i32 x, i32 y) -> i32 {\n"
							  "10*(2+4)*5+10-5/3*4;\n"
							  "5+2\n"
							  "}\n"
							  "function boop(f32 x, f32 y) -> i32\n"
							  "{\n"
							  "\t4 * 9\n"
							  "}");
	//input += getchar();
	//std::cin >> input;
	return input;
}

void Shell::executeCode(std::string code)
{
	_compiler.feed(code);
}

}