//
// Created by Citiral on 23/09/2015.
//

#include "FunctionCallDAST.h"

namespace ola {
    FunctionCallDAST::FunctionCallDAST(DastContext& context, std::string name,
                                            std::vector<std::unique_ptr<ExpressionDAST>> args) :
            ExpressionDAST(context),
            _func(name),
            _args(std::move(args)) {
        _type = context.getFunction(name)->getType();
    }

    Type* ola::FunctionCallDAST::getType() {
        return _type;
    }

    llvm::Value* FunctionCallDAST::codegen(Context* c) {
        llvm::Function* func = c->getScope()->getFunction(_func);
        CODEGEN_ASSERT(func != nullptr, "Undefined function " << _func);
        std::vector<llvm::Value*> args;
        for (u32 i = 0; i < _args.size(); i++) {
            args.push_back(_args[i]->codegen(c));
            //the argument needs to be valid
            if (args.back() == nullptr)
                return nullptr;
            //check if the type is valid
            CODEGEN_ASSERT(func->getFunctionType()->params()[i] == args.back()->getType(),
                           "Invalid type in function call. Expected " << func->getFunctionType()->params()[i] <<
                           " got " << args.back()->getType());

        }

        return c->builder.CreateCall(func, args, _func.c_str());
    }
}