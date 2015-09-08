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
    public:
        NumberIntegerAST(i64 value);

        void log(std::ostream &s) override;
        std::string type() override;

        static std::unique_ptr<NumberIntegerAST> generate(Lexer& l);

    private:
        i64 _value;
    };
}


#endif //OLA_NUMBERINTEGERAST_H
