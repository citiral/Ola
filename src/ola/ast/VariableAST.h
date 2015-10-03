//
// Created by citiral on 9/8/15.
//

#ifndef OLA_VARIABLEAST_H
#define OLA_VARIABLEAST_H

#include "ExpressionAST.h"

namespace ola {
    class VariableAST : public ExpressionAST {
    AST_NODE
    public:
        VariableAST(std::string name);

        Type* getType() override;
        std::string getName();
        void setType(Type* type);

    private:
        Type* _type;
        std::string _name;
    };
}


#endif //OLA_VARIABLEAST_H
