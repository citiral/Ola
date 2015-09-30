//
// Created by citiral on 9/23/15.
//

#ifndef OLA_FUNCTIONPROTOTYPEDAST_H
#define OLA_FUNCTIONPROTOTYPEDAST_H

#include "DASTNode.h"
#include "../type/Type.h"
#include <string>
#include <vector>
#include <llvm/IR/Function.h>
#include "../codegen/Context.h"

namespace ola {

	class FunctionPrototypeDAST : public DASTNode {
	public:
		FunctionPrototypeDAST(DastContext& context, std::string name, std::string type, std::vector<std::string> args);

		Type* getType();

		llvm::Function* codegen(Context* c);

	private:
		std::string _name;

		std::vector<std::string> _args;
	};

}


#endif //OLA_FUNCTIONPROTOTYPEDAST_H
