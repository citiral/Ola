//
// Created by citiral on 9/8/15.
//

#ifndef OLA_VARIABLEAST_H
#define OLA_VARIABLEAST_H

#include "ExpressionAST.h"

namespace ola {
    class VariableAST : public ExpressionAST {
    public:
        VariableAST(std::string name, std::string type);

        std::string type() { return _type; }

    private:
        std::string _name;
        std::string _type;
    };
}


#endif //OLA_VARIABLEAST_H
