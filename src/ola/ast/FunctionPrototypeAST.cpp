//
// Created by citiral on 9/8/15.
//

#include "FunctionPrototypeAST.h"
#include "../types.h"
#include "../compileassert.h"

namespace ola {
    FunctionPrototypeAST::FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args,
                                               std::vector<std::string> types)
            : _type(type),
              _name(name),
              _args(std::move(args)),
              _types(types) { }

    void FunctionPrototypeAST::log(std::ostream &s) {
        s << "Function prototype: " << _name << "(";
        if (_args.size() > 0)
            s << _types[0] << " " << _args[0];
        for (u32 i = 1; i < _args.size(); i++) {
            s << ", " << _types[i] << " " << _args[i];
        }
        s << ") -> " << _type << "\n";
    }

    std::string FunctionPrototypeAST::type() {
        return _type;
    }

    std::unique_ptr<FunctionPrototypeAST> FunctionPrototypeAST::generate(Lexer &l) {
        //eat the function token
        l.nextToken();
        //get the name of the function and eat it
        COMPILE_ASSERT(l.curToken() == Token::Identifier, "Expected identifier in function prototype.");
        std::string name = l.value.string;
        l.nextToken();

        std::vector<std::string> args;
        std::vector<std::string> types;
        std::string type;

        //make sure we are now in brackets
        COMPILE_ASSERT(l.curToken() == Token::Char_openRoundBracket, "Expected '(' after function identifier.");

        //keep fetching pairs of tokens until we have no more commas
        do {
            l.nextToken();
            //eat the type
            COMPILE_ASSERT(l.curToken() == Token::Identifier || l.curToken() == Token::Type, "Parameter should start with a type.");
            types.push_back(l.value.string);
            l.nextToken();
            //and the name
            COMPILE_ASSERT(l.curToken() == Token::Identifier, "Parameter should end with an identifier.");
            args.push_back(l.value.string);
            l.nextToken();
        } while (l.curToken() == Token::Char_comma);

        //brackets should be closed
        COMPILE_ASSERT(l.curToken() == Token::Char_closeRoundBracket, "Expected ')' after function argument list.");
        l.nextToken();
        //if the next token is a ->, we get the type
        if (l.curToken() == Token::Char_arrow) {
            l.nextToken();
            COMPILE_ASSERT(l.curToken() == Token::Identifier || l.curToken() == Token::Type, "Function return type is not a type.");
            type = l.value.string;
            l.nextToken();
        } else {
            type = "void";
        }
        return std::make_unique<FunctionPrototypeAST>(type, name, std::move(args), std::move(types));
    }
}