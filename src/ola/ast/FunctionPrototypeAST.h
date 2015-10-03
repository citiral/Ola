//
// Created by citiral on 9/8/15.
//

#ifndef OLA_FUNCTIONPROTOTYPEAST_H
#define OLA_FUNCTIONPROTOTYPEAST_H

#include "ASTNode.h"
#include "../lexer.h"
#include "../type/Type.h"
#include <memory>
#include <vector>
#include <llvm/IR/Function.h>

namespace ola {

    class FunctionPrototypeAST : public ASTNode {
    AST_NODE
    public:
        FunctionPrototypeAST(std::string type, std::string name, std::vector<std::string> args,
                             std::vector<std::string> types);

        //generates this node from the current state of the lexer.
        static std::unique_ptr<FunctionPrototypeAST> generate(Lexer &l);

        Type* getType();
        void setType(Type* type);
        std::string getTypeName();
        std::string getFunctionName();
        const std::vector<Type*>& getArgsTypes();
        void setArgsTypes(std::vector<Type*> argsTypes);
        const std::vector<std::string>& getArgsNames();
        const std::vector<std::string>& getArgsTypesNames();

    private:

        Type* _type;
        std::string _typeName;
        std::string _name;
        std::vector<Type*> _argsTypes;
        std::vector<std::string> _args;
        std::vector<std::string> _argsTypesNames;
    };

}

#endif //OLA_FUNCTIONPROTOTYPEAST_H
