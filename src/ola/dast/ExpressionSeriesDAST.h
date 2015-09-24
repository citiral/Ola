//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_EXPRESSIONSERIESDAST_H
#define OLA_EXPRESSIONSERIESDAST_H

#include "ExpressionDAST.h"
#include <vector>

namespace ola {

    class ExpressionSeriesDAST : public ExpressionDAST {
    public:
        ExpressionSeriesDAST(DastContext& dt, std::vector<std::unique_ptr<ExpressionDAST>> body);
        Type* getType() override;

        virtual llvm::Value* codegen(Context* c) override;

    private:
        std::vector <std::unique_ptr<ExpressionDAST>> _body;
    };

}


#endif //OLA_EXPRESSIONSERIESDAST_H
