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
	while (!_shouldStop) {
		_compiler.setCallback(std::bind(&Shell::getInput, this));
		_compiler.compileProgram();
	}
	return 0;
}

void Shell::scheduleExit()
{
	_shouldStop = true;
}

std::string Shell::getInput()
{
	/*static int i = 0;
	std::string input = "";
	if (i == 0)
		input = std::string("\nfunction add(i32 x, i32 y) -> i32 {\n"
							  "\tx+y\n"
							  "}\n"
			                  "function main() -> i32\n"
			                  "{\n"
			                  "\tadd(2+5+70,2*3+4*5)\n"
			                  "}");
	i++;*/
	std::string input;
	std::cin >> input;
	if (input.compare("QUIT") == 0)
		return std::string("");
	return input;
}

}