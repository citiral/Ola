//
// Created by Citiral on 16/09/2015.
//

#include <llvm/ADT/STLExtras.h>
#include "TypeList.h"
#include "PrimitiveType.h"

ola::TypeList::TypeList() {
    //define the primitive types
    definePrimitiveTypes();
}

void ola::TypeList::definePrimitiveTypes() {
    insertType("f32", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_F32, "f32"));
    insertType("f64", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_F64, "f64"));
    insertType("i8", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_I8, "i8"));
    insertType("i16", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_I16, "i16"));
    insertType("i32", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_I32, "i32"));
    insertType("i64", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_I64, "i64"));
    insertType("void", llvm::make_unique<PrimitiveType>(TypeType::PRIMITIVE_VOID, "void"));
}

bool ola::TypeList::hasType(std::string name) {
    return _types.find(name) != _types.end();
}

ola::Type *ola::TypeList::getType(std::string name) {
    return _types[name].get();
}

void ola::TypeList::insertType(std::string name, std::unique_ptr<ola::Type> _type) {
    _types.insert(std::pair<std::string, std::unique_ptr<Type> >(name, std::move(_type)));
}
