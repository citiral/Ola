//
// Created by citiral on 9/8/15.
//

#ifndef OLA_EXPRESSIONSERIESAST_H
#define OLA_EXPRESSIONSERIESAST_H

#include "ExpressionAST.h"
#include "../types.h"
#include <memory>
#include <vector>
#include "../lexer.h"
#include "../dast/ExpressionSeriesDAST.h"

namespace ola {
    class ExpressionSeriesAST : public ExpressionAST {
    public:
        ExpressionSeriesAST(std::vector<std::unique_ptr<ExpressionAST>> body);

        virtual void log(std::ostream &s) override;
        virtual llvm::Value* codegen(Context* c) override;

        static std::unique_ptr<ExpressionSeriesAST> generate(Lexer& l);

        std::unique_ptr<ExpressionDAST> generateDecoratedTree(DastContext& context) override;
        //this is ugly, but needs to be done since unique_ptrs don't support covariance
        std::unique_ptr<ExpressionSeriesDAST> generateDecoratedTreeExpressionSeries(DastContext& context);

    private:
        std::vector<std::unique_ptr<ExpressionAST>> _body;
    };
}


#endif //OLA_EXPRESSIONSERIESAST_H
