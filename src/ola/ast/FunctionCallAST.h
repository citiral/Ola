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
        NODE_VISITOR_FUNCTIONS
        FunctionCallAST(std::string func, std::vector<std::unique_ptr<ExpressionAST>> args);

        virtual void log(std::ostream &s) override;

        std::unique_ptr<DASTNode> generateDecoratedTree(DastContext& context) override;
        std::unique_ptr<ExpressionDAST> generateDecoratedTreeExpression(DastContext& context) override;

        //generates a functioncallast from the current state of the lexer. The functionname must already be parsed
        static std::unique_ptr<FunctionCallAST> generate(std::string functionname, Lexer& l);

        Type* getType() override;
    private:
        Type* _type;
        std::string _func;
        std::vector<std::unique_ptr<ExpressionAST>> _args;
    };
}


#endif //OLA_FUNCTIONCALLAST_H
