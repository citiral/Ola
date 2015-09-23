//
// Created by citiral on 9/23/15.
//

#include "VariableDAST.h"

ola::VariableDAST::VariableDAST(ola::DastContext& dc, std::string name):
	ExpressionDAST(dc),
	_name(name) {
	_type = dc.variableStack->getVariable(_name);
}

ola::Type* ola::VariableDAST::getType() {
	return _type;
}
