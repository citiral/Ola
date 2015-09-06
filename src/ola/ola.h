#pragma once
#include <string>
#include "lexer.h"

namespace ola {

/**
 * Use this class to compile Ola code to Llvm
 */
class OlaToLlvmCompiler {
public:
	OlaToLlvmCompiler();
	~OlaToLlvmCompiler();

	//feeds the compiler with the given code, which in turn gets immediately compiled.
	void feed(std::string code);

private:
	Lexer _lexer;

};


}