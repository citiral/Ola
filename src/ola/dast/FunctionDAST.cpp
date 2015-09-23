//
// Created by Citiral on 23/09/2015.
//

#include "FunctionDAST.h"

ola::FunctionDAST::FunctionDAST(ola::DastContext& context, std::unique_ptr<ola::FunctionPrototypeDAST> prototype,
                                std::unique_ptr<ola::ExpressionSeriesDAST> body):
    DASTNode(context),
    _prototype(std::move(prototype)),
    _body(std::move(body)) {

}
