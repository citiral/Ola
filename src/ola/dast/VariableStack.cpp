//
// Created by citiral on 9/23/15.
//

#include "VariableStack.h"

namespace ola {

	VariableStack::VariableStack() :
			_parent(nullptr) {

	}

	VariableStack::VariableStack(std::unique_ptr<VariableStack> parent) :
			_parent(std::move(parent)) {

	}

	std::unique_ptr<VariableStack> VariableStack::getParent() {
		return std::move(_parent);
	}

	Type* VariableStack::getVariable(std::string name) {
		return _variables[name];
	}

	void VariableStack::setVariable(std::string name, Type* type) {
		_variables[name] = type;
	}

	void VariableStack::removeVariable(std::string name) {
		_variables.erase(_variables.find(name));
	}
}