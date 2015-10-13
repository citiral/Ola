//
// Created by citiral on 9/8/15.
//

#ifndef OLA_NUMBERINTEGERAST_H
#define OLA_NUMBERINTEGERAST_H

#include "ExpressionAST.h"
#include "../types.h"
#include "../lexer.h"
#include <memory>

namespace ola {
    class NumberIntegerAST : public ExpressionAST {
    AST_NODE
    public:
        NumberIntegerAST(Lexer& l, i32 value);

        static std::unique_ptr<NumberIntegerAST> generate(Lexer& l);

        Type* getType() override;
        void setType(Type* type);
        i32 getValue();

    private:
        Type* _type;
        i32 _value;
    };
}


#endif //OLA_NUMBERINTEGERAST_H
