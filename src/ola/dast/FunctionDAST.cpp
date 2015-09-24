//
// Created by Citiral on 23/09/2015.
//

#include "FunctionDAST.h"
#include <iostream>

namespace ola {
    FunctionDAST::FunctionDAST(ola::DastContext& context, std::unique_ptr<ola::FunctionPrototypeDAST> prototype,
                                    std::unique_ptr<ola::ExpressionSeriesDAST> body) :
            DASTNode(context),
            _prototype(std::move(prototype)),
            _body(std::move(body)) {
        std::cout << "created function dast\n";
    }

    llvm::Function* FunctionDAST::codegen(Context* c) {
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
        func->dump();
        std::cout << "aaaa\n";
        return func;
    }

}