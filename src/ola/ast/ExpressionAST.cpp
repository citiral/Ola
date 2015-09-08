//
// Created by citiral on 9/8/15.
//

#include "ExpressionAST.h"
#include "NumberIntegerAST.h"
#include "../compileassert.h"
#include "BinaryOperatorAST.h"

namespace ola {
    ExpressionAST::~ExpressionAST() {
    }

    std::unique_ptr<ExpressionAST> ExpressionAST::generate(Lexer &l) {
        //try to parse the expression as a primary
        auto LHS = generatePrimary(l);

        //the next token can either be '(' which initiates a call, or an operator
        if (l.curToken() == Token::Operator) {
            LHS = std::move(BinaryOperatorAST::generate(l, std::move(LHS)));
        }

        return LHS;
    }

    std::unique_ptr<ExpressionAST> ExpressionAST::generatePrimary(Lexer &l) {
        switch (l.curToken()) {
            default:
                COMPILE_GENERATE_AND_RETURN_ERROR(l, "Unknown token in expression");
            case Token::Numeric:
                return NumberIntegerAST::generate(l);
            case Token::Identifier:
                COMPILE_GENERATE_AND_RETURN_TODO(l, "Implement identifiers in expression.");
            case Token::Char_openRoundBracket:
                //eat the round bracket
                l.nextToken();
                //generate the value inside the brackets
                auto value = generate(l);
                //we should have a closing bracket now.
                COMPILE_ASSERT(l.curToken() == Token::Char_closeRoundBracket, "Bracket not closed around expression.");
                l.nextToken();
                return std::move(value);
        }
    }
}