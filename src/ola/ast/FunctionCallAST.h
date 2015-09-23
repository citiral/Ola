//
// Created by citiral on 9/9/15.
//

#ifndef OLA_FUNCTIONCALLAST_H
#define OLA_FUNCTIONCALLAST_H

#include "ExpressionAST.h"
#include <vector>
namespace ola {

    class FunctionCallAST : public ExpressionAST {
    public:
        FunctionCallAST(std::string func, std::vector<std::unique_ptr<ExpressionAST>> args);

        virtual void log(std::ostream &s) override;
        virtual llvm::Value* codegen(Context* c) override;

        std::unique_ptr<ExpressionDAST> generateDecoratedTree(DastContext& context) override;

        //generates a functioncallast from the current state of the lexer. The functionname must already be parsed
        static std::unique_ptr<FunctionCallAST> generate(std::string functionname, Lexer& l);
    private:
        std::string _func;
        std::vector<std::unique_ptr<ExpressionAST>> _args;
    };
}


#endif //OLA_FUNCTIONCALLAST_H
