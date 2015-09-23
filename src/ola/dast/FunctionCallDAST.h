//
// Created by Citiral on 23/09/2015.
//

#ifndef OLA_FUNCTIONCALLDAST_H
#define OLA_FUNCTIONCALLDAST_H

#include <vector>
#include "ExpressionDAST.h"
#include "FunctionPrototypeDAST.h"

namespace ola {

    class FunctionCallDAST : public ExpressionDAST {
    public:
        FunctionCallDAST(DastContext& context, std::string name, std::vector<std::unique_ptr<ExpressionDAST>> args);

        Type* getType() override;

    private:
        Type* _type;
        std::string _func;
        std::vector<std::unique_ptr<ExpressionDAST>> _args;
    };
}


#endif //OLA_FUNCTIONCALLDAST_H
