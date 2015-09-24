//
// Created by citiral on 9/8/15.
//

#ifndef OLA_VARIABLEAST_H
#define OLA_VARIABLEAST_H

#include "ExpressionAST.h"

namespace ola {
    class VariableAST : public ExpressionAST {
    public:
        VariableAST(std::string name);

        virtual void log(std::ostream &s);

        std::unique_ptr<DASTNode> generateDecoratedTree(DastContext& context) override;
        std::unique_ptr<ExpressionDAST> generateDecoratedTreeExpression(DastContext& context) override;

    private:
        std::string _name;
    };
}


#endif //OLA_VARIABLEAST_H
