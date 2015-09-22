//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_NUMBERINTEGERDAST_H
#define OLA_NUMBERINTEGERDAST_H

#include "../types.h"
#include "ExpressionDAST.h"

namespace ola {

    class NumberIntegerDAST : public ExpressionDAST {
    public:
        NumberIntegerDAST(DastContext& dt, i32 value);
        Type* getType() override;
    private:
        i32 _value;
    };

}


#endif //OLA_NUMBERINTEGERDAST_H
