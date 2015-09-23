//
// Created by citiral on 9/23/15.
//

#ifndef OLA_VARIABLESTACK_H
#define OLA_VARIABLESTACK_H

#include <memory>
#include <map>
#include "../type/Type.h"

namespace ola {
	class VariableStack {
	public:
		VariableStack();
		VariableStack(std::unique_ptr<VariableStack> parent);

		Type* getVariable(std::string name);
		void setVariable(std::string name, Type* type);
		void removeVariable(std::string name);

		std::unique_ptr<VariableStack> getParent();

	private:
		std::map<std::string, Type*> _variables;
		std::unique_ptr<VariableStack> _parent;
	};
}


#endif //OLA_VARIABLESTACK_H
