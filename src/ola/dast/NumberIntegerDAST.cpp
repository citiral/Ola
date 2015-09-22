//
// Created by Citiral on 16/09/2015.
//

#include "NumberIntegerDAST.h"

namespace ola {


NumberIntegerDAST::NumberIntegerDAST(DastContext& dt, i32 value):
    ExpressionDAST(dt),
    _value(value) {

}

Type* NumberIntegerDAST::getType() {
    return _context.typeList.getType("i32");
}

}