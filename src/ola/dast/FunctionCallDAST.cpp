//
// Created by Citiral on 23/09/2015.
//

#include "FunctionCallDAST.h"

ola::FunctionCallDAST::FunctionCallDAST(ola::DastContext& context, std::string name,
                                        std::vector<std::unique_ptr<ola::ExpressionDAST>> args):
    ExpressionDAST(context),
    _func(name),
    _args(std::move(args)) {
    _type = context.getFunction(name)->getType();
}

ola::Type* ola::FunctionCallDAST::getType() {
    return _type;
}
