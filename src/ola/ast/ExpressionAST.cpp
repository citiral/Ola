//
// Created by citiral on 9/8/15.
//

#include <llvm/ADT/STLExtras.h>
#include "../astassert.h"
#include "ExpressionAST.h"
#include "NumberIntegerAST.h"
#include "BinaryOperatorAST.h"
#include "VariableAST.h"
#include "FunctionCallAST.h"

namespace ola {
    ExpressionAST::~ExpressionAST() {
    }

    std::unique_ptr<ExpressionAST> ExpressionAST::generate(Lexer &l) {
        //try to parse the expression as a primary
        auto LHS = generatePrimary(l);

        //if the next token is an operator, parse it
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
                return generateIdentifier(l);
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

    std::unique_ptr<ExpressionAST> ExpressionAST::generateIdentifier(Lexer &l) {
        //get the name and eat it
        std::string identifiername = l.value.string;
        l.nextToken();

        //if the next token is a '(', it is a function call
        if (l.curToken() == Token::Char_openRoundBracket) {
            return FunctionCallAST::generate(identifiername, l);
        }

        //otherwise, we just return it as a variable ast
        return llvm::make_unique<VariableAST>(identifiername);
    }

}