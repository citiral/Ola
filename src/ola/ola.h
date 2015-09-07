#pragma once
#include <string>
#include "lexer.h"
#include "ast.h"

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

	//compiles the program using the tokens the lexer will return
	void compileProgram();
	void compileNumeric();
	void compileBlock();
	//curtok should equal the first unparsed token after exiting a function
	Token _curTok;
	Lexer _lexer;

};


}