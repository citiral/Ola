//
// Created by citiral on 9/8/15.
//

#include "VariableAST.h"
#include "../codegenassert.h"
#include "../dast/VariableDAST.h"

namespace ola {
    VariableAST::VariableAST(std::string name)
            : _name(name) { }

    void VariableAST::log(std::ostream &s) {
        s << "var: " << _name;
    }

    std::unique_ptr<DASTNode> VariableAST::generateDecoratedTree(DastContext& context) {
        return generateDecoratedTreeExpression(context);
    }

    std::unique_ptr<ExpressionDAST> VariableAST::generateDecoratedTreeExpression(DastContext& context) {
        return llvm::make_unique<VariableDAST>(context, _name);
    }
}