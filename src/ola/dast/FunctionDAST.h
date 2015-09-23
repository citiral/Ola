//
// Created by Citiral on 23/09/2015.
//

#ifndef OLA_FUNCTIONDAST_H
#define OLA_FUNCTIONDAST_H

#include "DASTNode.h"
#include "FunctionPrototypeDAST.h"
#include "ExpressionSeriesDAST.h"

namespace ola {

    class FunctionDAST : public DASTNode {
    public:
        FunctionDAST(DastContext&, std::unique_ptr<FunctionPrototypeDAST> prototype, std::unique_ptr<ExpressionSeriesDAST> body);

    private:
        std::unique_ptr<FunctionPrototypeDAST> _prototype;
        std::unique_ptr<ExpressionSeriesDAST> _body;
    };

}


#endif //OLA_FUNCTIONDAST_H
