//
// Created by Citiral on 16/09/2015.
//

#include "DastContext.h"
#include <llvm/ADT/STLExtras.h>
#include "FunctionPrototypeDAST.h"

namespace ola {
	DastContext::DastContext() :
			variableStack(llvm::make_unique<VariableStack>(nullptr)) {
	}

	void DastContext::pushVariableStack() {
		variableStack = llvm::make_unique<VariableStack>(std::move(variableStack));
	}

	void DastContext::popVariableStack() {
		variableStack = std::move(variableStack->getParent());
	}

	FunctionPrototypeDAST* DastContext::getFunction(std::string string) {
		return _functionMap[string];
	}

	void DastContext::setFunction(std::string string, FunctionPrototypeAST* function) {
		_functionMap[string] = function;
	}

	void DastContext::removeFunction(std::string string) {
		_functionMap.erase(string);
	}
}
