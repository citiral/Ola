//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_EXPRESSIONKILLERDAST_H
#define OLA_EXPRESSIONKILLERDAST_H

#include "ExpressionDAST.h"

namespace ola {

    class ExpressionKillerDAST : public ExpressionDAST {
    public:
        ExpressionKillerDAST(DastContext& dt, std::unique_ptr<ExpressionDAST> expression);
        virtual Type* getType();

    private:
        std::unique_ptr<ExpressionDAST> _expression;
    };

}


#endif //OLA_EXPRESSIONKILLERDAST_H
