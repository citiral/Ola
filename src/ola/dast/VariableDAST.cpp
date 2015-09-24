//
// Created by citiral on 9/23/15.
//

#include "VariableDAST.h"

namespace ola {

	VariableDAST::VariableDAST(ola::DastContext& dc, std::string name) :
			ExpressionDAST(dc),
			_name(name) {
		_type = dc.variableStack->getVariable(_name);
	}

	Type* ola::VariableDAST::getType() {
		return _type;
	}

	llvm::Value* VariableDAST::codegen(Context* c) {
		llvm::Value* value = c->getScope()->getVariable(_name);
		CODEGEN_ASSERT(value != nullptr, "Undefined variable " << _name);
		return value;
	}

}