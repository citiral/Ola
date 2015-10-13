//
// Created by citiral on 9/9/15.
//

#ifndef OLA_FUNCTIONCALLAST_H
#define OLA_FUNCTIONCALLAST_H

#include "ExpressionAST.h"
#include <vector>
namespace ola {

    class FunctionCallAST : public ExpressionAST {
    AST_NODE
    public:
        FunctionCallAST(Lexer& l, std::string func, std::vector<std::unique_ptr<ExpressionAST>> args);

        //generates a functioncallast from the current state of the lexer. The functionname must already be parsed
        static std::unique_ptr<FunctionCallAST> generate(std::string functionname, Lexer& l);

        Type* getType() override;
        void setType(Type* type);
        std::string getFunctionName();
        std::vector<std::unique_ptr<ExpressionAST>>* getArgs();

    private:
        Type* _type;
        std::string _func;
        std::vector<std::unique_ptr<ExpressionAST>> _args;
    };
}


#endif //OLA_FUNCTIONCALLAST_H
