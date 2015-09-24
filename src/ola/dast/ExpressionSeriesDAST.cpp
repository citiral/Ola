//
// Created by Citiral on 16/09/2015.
//

#include "ExpressionSeriesDAST.h"
#include "../types.h"

namespace ola {
    ExpressionSeriesDAST::ExpressionSeriesDAST(DastContext& dt,
                                                    std::vector<std::unique_ptr<ola::ExpressionDAST>> body):
        ExpressionDAST(dt),
        _body(std::move(body)) {
    }

    Type* ola::ExpressionSeriesDAST::getType() {
        return _body[_body.size()-1]->getType();
    }

    llvm::Value* ExpressionSeriesDAST::codegen(Context* c) {
        llvm::Value* last = nullptr;
        for (u32 i = 0 ; i < _body.size() ; i++)
            last = _body[i]->codegen(c);
        return last;
    }
}