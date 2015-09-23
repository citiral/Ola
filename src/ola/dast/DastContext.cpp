//
// Created by Citiral on 16/09/2015.
//

#include "DastContext.h"
#include <llvm/ADT/STLExtras.h>

ola::DastContext::DastContext():
	variableStack(llvm::make_unique<VariableStack>(nullptr)) {
}

void ola::DastContext::pushVariableStack() {
	variableStack = llvm::make_unique<VariableStack>(std::move(variableStack));
}

void ola::DastContext::popVariableStack() {
	variableStack = std::move(variableStack->getParent());
}
