//
// Created by citiral on 9/8/15.
//

#ifndef OLA_FUNCTIONPROTOTYPEAST_H
#define OLA_FUNCTIONPROTOTYPEAST_H

#include "ASTNode.h"
#include "../lexer.h"
#include "../codegen/Context.h"
#include <memory>
#include <vector>
#include <llvm/IR/Function.h>

namespace ola {

    class FunctionPrototypeAST : public ASTNode {
    public:
        FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args,
                             std::vector<std::string> types);

        virtual void log(std::ostream &s);
        llvm::Function* codegen(Context* c);

        //generates this node from the current state of the lexer.
        static std::unique_ptr<FunctionPrototypeAST> generate(Lexer &l);

    private:
        std::string _type;
        std::string _name;
        std::vector<std::string> _args;
        std::vector<std::string> _types;
    };

}

#endif //OLA_FUNCTIONPROTOTYPEAST_H
