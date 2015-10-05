//
// Created by Citiral on 3/10/2015.
//

#include <llvm/IR/Verifier.h>
#include "CodegenPass.h"
#include "../ast/BinaryOperatorAST.h"
#include "../ast/ExpressionKillerAST.h"
#include "../ast/ExpressionSeriesAST.h"
#include "../ast/FunctionPrototypeAST.h"
#include "../ast/FunctionAST.h"
#include "../ast/FunctionCallAST.h"
#include "../ast/NumberIntegerAST.h"
#include "../ast/VariableAST.h"

namespace ola {

    CodegenPass::CodegenPass(Context& c):
        _c(c) {
    }

    void CodegenPass::accept(ASTNode* ast) {
        PASS_ERROR("Cannot godegen ASTNode.");
    }

    void CodegenPass::accept(BinaryOperatorAST* ast) {
        auto lhs = visitAndPop(ast->getLeftExpression());
        auto rhs = visitAndPop(ast->getRightExpression());

        //if one of the ends is invalid, this one will be too
        if (lhs == nullptr || rhs == nullptr)
            PUSH_AND_RETURN(nullptr);

        if (ast->getOperator() == '+')
            PUSH_AND_RETURN(_c.llvmBuilder.CreateAdd(lhs, rhs, "tempbinadd"));
        if (ast->getOperator() == '-')
            PUSH_AND_RETURN(_c.llvmBuilder.CreateSub(lhs, rhs, "tempbindiv"));
        if (ast->getOperator() == '*')
            PUSH_AND_RETURN(_c.llvmBuilder.CreateMul(lhs, rhs, "tempbinmul"));
        if (ast->getOperator() == '/')
            PUSH_AND_RETURN(_c.llvmBuilder.CreateSDiv(lhs, rhs, "tempbinsdiv"));

        PASS_ASSERT(false, "Invalid binary operator.");
    }

    void CodegenPass::accept(ExpressionAST* ast) {
        PASS_ERROR("Cannot godegen ASTNode.");
    }

    void CodegenPass::accept(ExpressionKillerAST* ast) {
        ast->visit(*this);
        PUSH_AND_RETURN(llvm::UndefValue::get(_c.llvmBuilder.getVoidTy()));
    }

    void CodegenPass::accept(ExpressionSeriesAST* ast) {
        llvm::Value* last = nullptr;
        for (u32 i = 0 ; i < ast->getBody()->size() ; i++)
            last = visitAndPop(ast->getBody()->at(i).get());
        PUSH_AND_RETURN(last);
    }

    void CodegenPass::accept(FunctionAST* ast) {
        //TODO extern functions
        //TODO erase invalid functions

        //get the function from the prototype
        ast->getPrototype()->visit(*this);
        llvm::Function* func = _c.llvmFunctions.getValue(ast->getPrototype()->getFunctionName());

        if (func == nullptr)
            PUSH_AND_RETURN(nullptr);

        //create the base building block to insert code into
        llvm::BasicBlock* BB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "funcentry", func);
        _c.llvmBuilder.SetInsertPoint(BB);

        //push a new scope onto the stack
        _c.pushAll();

        // Record the function arguments in the NamedValues map.
        for (auto &Arg : func->args()) {
            _c.llvmVariables.addValue(Arg.getName(), &Arg);
        }

        //codegen the body
        auto code = visitAndPop(ast->getExpressionSeries());

        //pop the scope
        _c.popAll();

        //if the body is invalid, abort
        if (code == nullptr) {
            PUSH_AND_RETURN(nullptr);
        }

        //return the body
        _c.llvmBuilder.CreateRet(code);

        //validate and return
        llvm::verifyFunction(*func);

        _c.llvmFunctions.addValue(ast->getPrototype()->getFunctionName(), func);
        return;
    }

    void CodegenPass::accept(FunctionCallAST* ast) {
        //get the llvm function
        llvm::Function* func = _c.llvmFunctions.getValue(ast->getFunctionName());
        PASS_ASSERT(func != nullptr, "Undefined function " << ast->getFunctionName());

        //compile all the arguments
        std::vector<llvm::Value*> args;
        for (u32 i = 0; i < ast->getArgs()->size(); i++) {
            //compile the argument
            args.push_back(visitAndPop(ast->getArgs()->at(i).get()));

            //the argument needs to be valid
            if (args.back() == nullptr)
                PUSH_AND_RETURN(nullptr);

            //check if the type is valid
            PASS_ASSERT(func->getFunctionType()->params()[i] == args.back()->getType(),
                           "Invalid type in function call. Expected " << func->getFunctionType()->params()[i] <<
                           " got " << args.back()->getType());
        }

        PUSH_AND_RETURN(_c.llvmBuilder.CreateCall(func, args, ast->getFunctionName().c_str()));
    }

    void CodegenPass::accept(FunctionPrototypeAST* ast) {
        std::vector<llvm::Type*> types;

        //first, parse all the types
        for (u32 i = 0 ; i < ast->getArgsTypes().size() ; i++) {
            llvm::Type* t = ast->getArgsTypes().at(i)->getLlvmType(&_c.llvmBuilder);
            PASS_ASSERT(t != nullptr, "Unknown type " << ast->getArgsTypes().at(i));
            types.push_back(t);
        }

        //get the function type
        llvm::FunctionType* funcType = llvm::FunctionType::get(ast->getType()->getLlvmType(&_c.llvmBuilder), types, false);

        //and create the function
        llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, ast->getFunctionName(), &_c.llvmModule);

        //set the names of the arguments
        u32 i = 0;
        for (auto& arg : func->args()) {
            arg.setName(ast->getArgsNames()[i++]);
        }

        //insert the function into the context
        _c.llvmFunctions.addValue(ast->getFunctionName(), func);

        return;
    }

    void CodegenPass::accept(NumberIntegerAST* ast) {
        PUSH_AND_RETURN(_c.llvmBuilder.getInt32(ast->getValue()));
    }

    void CodegenPass::accept(VariableAST* ast) {
        llvm::Value* value = _c.llvmVariables.getValue(ast->getName());
        PASS_ASSERT(value != nullptr, "Undefined variable " << ast->getName());
        PUSH_AND_RETURN(value);
    }
}