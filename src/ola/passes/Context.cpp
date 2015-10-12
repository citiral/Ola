//
// Created by Citiral on 30/09/2015.
//

#include "Context.h"
#include "../type/PrimitiveType.h"
#include <llvm/ADT/STLExtras.h>

namespace ola {
    Context::Context():
        llvmBuilder(llvm::getGlobalContext()),
        llvmModule("Ola", llvm::getGlobalContext()) {

        //TODO: delete this memory
        types.addValue("f32", new PrimitiveType(TypeType::PRIMITIVE_F32, "f32"));
        types.addValue("f64", new PrimitiveType(TypeType::PRIMITIVE_F64, "f64"));
        types.addValue("i8", new PrimitiveType(TypeType::PRIMITIVE_I8, "i8"));
        types.addValue("i16", new PrimitiveType(TypeType::PRIMITIVE_I16, "i16"));
        types.addValue("i32", new PrimitiveType(TypeType::PRIMITIVE_I32, "i32"));
        types.addValue("i64", new PrimitiveType(TypeType::PRIMITIVE_I64, "i64"));
        types.addValue("void", new PrimitiveType(TypeType::PRIMITIVE_VOID, "void"));
    }

    void Context::pushAll() {
        types.pushMap();
        variables.pushMap();
        functions.pushMap();
        llvmFunctions.pushMap();
        llvmVariables.pushMap();
    }

    void Context::popAll() {
        types.popMap();
        variables.popMap();
        functions.popMap();
        llvmFunctions.popMap();
        llvmVariables.popMap();
    }
}