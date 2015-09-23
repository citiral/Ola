//
// Created by citiral on 9/23/15.
//

#include "FunctionPrototypeDAST.h"
#include "../types.h"

namespace ola {
	FunctionPrototypeDAST::FunctionPrototypeDAST(DastContext& context, std::string name, std::string type, std::vector<std::string> args):
		DASTNode(context),
		_name(name),
		_args(std::move(args)),
		_type(context.typeList.getType(type)) {
		//generate all types
		for (u32 i = 0 ; i < _args.size() ; i++)
			_types.push_back(context.typeList.getType(_args[i]));
	}
}