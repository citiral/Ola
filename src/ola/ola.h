#pragma once

#include "lexer.h"
#include "types.h"
#include "ast.h"
#include "passes/Context.h"
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
	//lexes the program and returns an array of root nodes (the blocks in the program)
	std::vector<std::unique_ptr<ASTNode>> lexProgram();
	//runs a single pass over all nodes in the given array
	void runPass(std::vector<std::unique_ptr<ASTNode>>& nodes, AbstractPass& pass);

	std::unique_ptr<ASTNode> compileBlock();

	//curtok should equal the first unparsed token after exiting a function
	Lexer _lexer;
	//context on which all passes will run
	Context _c;
};

}