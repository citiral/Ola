//
// Created by Citiral on 14/09/2015.
//

#ifndef OLA_TYPE_H
#define OLA_TYPE_H

#include <string>
#include <functional>
#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>

namespace ola {

    class PrimitiveType;

    enum TypeType {
        PRIMITIVE_I8,
        PRIMITIVE_I16,
        PRIMITIVE_I32,
        PRIMITIVE_I64,
        PRIMITIVE_F32,
        PRIMITIVE_F64,
        PRIMITIVE_VOID,
        CLASS,
    };

    class Type {
    public:
        virtual ~Type() {};
        virtual TypeType getType() = 0;
        virtual bool equals(Type* t) = 0;
        virtual bool equals(PrimitiveType* t) = 0;
        virtual llvm::Type* getLlvmType(llvm::IRBuilder<>* builder) = 0;

    private:
    };

}


#endif //OLA_TYPE_H
