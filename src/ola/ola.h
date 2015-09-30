#pragma once
#include "lexer.h"
#include "types.h"
#include "ast.h"
#include <string>
#include <memory>

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

	std::unique_ptr<ASTNode> compileBlock();

	//curtok should equal the first unparsed token after exiting a function
	Lexer _lexer;
};

}