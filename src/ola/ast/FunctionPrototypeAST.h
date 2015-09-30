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
#include "../dast/FunctionPrototypeDAST.h"

namespace ola {

    class FunctionPrototypeAST : public ASTNode {
    public:
        NODE_VISITOR_FUNCTIONS
        FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args,
                             std::vector<std::string> types);

        virtual void log(std::ostream &s);

        //generates this node from the current state of the lexer.
        static std::unique_ptr<FunctionPrototypeAST> generate(Lexer &l);

        Type* getType();
        std::string getTypeName();
        std::string getFunctionName();
        void setType(Type* type);

    private:

        Type* _type;
        std::string _name;
        std::string _typeName;
        std::vector<Type*> _argsTypes;
        std::vector<std::string> _args;
        std::vector<std::string> _argsTypesNames;
    };

}

#endif //OLA_FUNCTIONPROTOTYPEAST_H
