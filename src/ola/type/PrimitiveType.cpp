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

    bool PrimitiveType::equals(PrimitiveType* t) {
        return t->_type == _type;
    }

    TypeType PrimitiveType::getType() {
        return _type;
    }

    llvm::Type* PrimitiveType::getLlvmType(llvm::IRBuilder<>* builder) {
        if (_type == TypeType::PRIMITIVE_I16)
            return builder->getInt16Ty();
        if (_type == TypeType::PRIMITIVE_I32)
            return builder->getInt32Ty();
        if (_type == TypeType::PRIMITIVE_I64)
            return builder->getInt64Ty();
        if (_type == TypeType::PRIMITIVE_F32)
            return builder->getFloatTy();
        if (_type == TypeType::PRIMITIVE_F64)
            return builder->getDoubleTy();
        else
            return nullptr;
    }
}