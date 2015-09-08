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
	std::unique_ptr<ASTNode> compileGenerateError(std::string error);
	std::unique_ptr<NumberIntegerAST> compileNumeric();
	std::unique_ptr<FunctionAST> compileFunction();
	std::unique_ptr<FunctionPrototypeAST> compileFunctionPrototype();
	std::unique_ptr<ExpressionSeriesAST> compileExpressionSeries();
	std::unique_ptr<ExpressionAST> compileExpression();

	//compilation helper functions
	Token nextToken();


	//curtok should equal the first unparsed token after exiting a function
	Token _curTok;
	Lexer _lexer;

};


}