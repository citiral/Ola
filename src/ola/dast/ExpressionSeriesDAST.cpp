//
// Created by Citiral on 16/09/2015.
//

#include "ExpressionSeriesDAST.h"

ola::ExpressionSeriesDAST::ExpressionSeriesDAST(ola::DastContext& dt,
                                                std::vector<std::unique_ptr<ola::ExpressionDAST>> body):
    ExpressionDAST(dt),
    _body(std::move(body)) {
}

ola::Type* ola::ExpressionSeriesDAST::getType() {
    return _body[_body.size()-1]->getType();
}
