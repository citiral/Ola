//
// Created by citiral on 9/8/15.
//

#ifndef OLA_FUNCTIONAST_H
#define OLA_FUNCTIONAST_H

#include "ASTNode.h"
#include "FunctionPrototypeAST.h"
#include "ExpressionSeriesAST.h"
#include <memory>

namespace ola {
    class FunctionAST : public ASTNode {
    public:
        FunctionAST(std::unique_ptr<FunctionPrototypeAST> prototype, std::unique_ptr<ExpressionSeriesAST> body);

        virtual void log(std::ostream &s) override;
        llvm::Function* codegen(Context* c);

        static std::unique_ptr<FunctionAST> generate(Lexer& l);

    private:
        std::unique_ptr<FunctionPrototypeAST> _prototype;
        std::unique_ptr<ExpressionSeriesAST> _body;
    };
}

#endif //OLA_FUNCTIONAST_H
