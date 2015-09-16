//
// Created by citiral on 9/8/15.
//

#include "FunctionAST.h"
#include "../astassert.h"
#include <llvm/IR/Function.h>

namespace ola {
    FunctionAST::FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body)
            : _prototype(std::move(prototype)),
              _body(std::move(body)) { }

    void FunctionAST::log(std::ostream &s) {
        _prototype->log(s);
        _body->log(s);
    }

    std::unique_ptr<FunctionAST> FunctionAST::generate(Lexer &l) {
        auto prototype = FunctionPrototypeAST::generate(l);

        //we should be at the brackets now
        COMPILE_ASSERT(l.curToken() == Token::Char_openCurlyBracket, "Expected { after function declaration.");
        l.nextToken();

        auto body = ExpressionSeriesAST::generate(l);

        //and it should be closed now
        COMPILE_ASSERT(l.curToken() == Token::Char_closeCurlyBracket, "Expected } At the end of the function body.");
        l.nextToken();

        return llvm::make_unique<FunctionAST>(std::move(prototype), std::move(body));
    }

    llvm::Function* FunctionAST::codegen(Context* c) {
	    //TODO extern functions
	    //TODO erase invalid functions

		//get the function from the prototype
	    llvm::Function* func = _prototype->codegen(c);

	    if (func == nullptr)
		    return nullptr;

	    //create the base building block to insert code into
	    llvm::BasicBlock* BB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "funcentry", func);
	    c->builder.SetInsertPoint(BB);

	    //push a new scope onto the stack
	    c->pushScope();

	    // Record the function arguments in the NamedValues map.
	    for (auto &Arg : func->args()) {
		    std::cout << "adding var " << Arg.getName().str() << "\n";
		    c->getScope()->addVariable(Arg.getName(), &Arg);
	    }

	    //codegen the body
	    auto code = _body->codegen(c);

	    //if the body is invalid, abort
	    if (code == nullptr) {
		    return nullptr;
	    }

	    //return the body
	    c->builder.CreateRet(code);

	    //validate and return
	    llvm::verifyFunction(*func);
	    return func;
    }
}