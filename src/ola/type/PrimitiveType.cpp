//
// Created by Citiral on 16/09/2015.
//

#include "PrimitiveType.h"

namespace ola{

    PrimitiveType::PrimitiveType(ola::TypeType primitiveType, std::string name)
    : _type(primitiveType),
    _name(name) {
    }

    bool PrimitiveType::equals(ola::Type* t) {
        return t->equals(this);
    }

    bool PrimitiveType::equals_handle(PrimitiveType* t) {
        return t->_type == _type;
    }

    TypeType PrimitiveType::getType() {
        return _type;
    }
}