//
// Created by citiral on 9/23/15.
//

#include "FunctionPrototypeDAST.h"
#include "../types.h"
#include "../codegenassert.h"

namespace ola {
	FunctionPrototypeDAST::FunctionPrototypeDAST(DastContext& context, std::string name, std::string type, std::vector<std::string> args):
		DASTNode(context),
		_type(context.typeList.getType(type)),
		_name(name),
		_args(std::move(args)) {
		//generate all types
		for (u32 i = 0 ; i < _args.size() ; i++)
			_types.push_back(context.typeList.getType(_args[i]));
	}

	Type* FunctionPrototypeDAST::getType() {
		return _type;
	}

	llvm::Function* FunctionPrototypeDAST::codegen(Context* c) {
		std::vector<llvm::Type*> types;

		//first, parse all the types
		for (u32 i = 0 ; i < _types.size() ; i++) {
			llvm::Type* t = _types[i]->getLlvmType(&c->builder);
			CODEGEN_ASSERT(t != nullptr, "Unknown type " << _types[i]);
			types.push_back(t);
		}

		llvm::FunctionType* funcType = llvm::FunctionType::get(_type->getLlvmType(&c->builder), types, false);
		llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, _name, c->module.get());

		u32 i = 0;
		for (auto& arg : func->args()) {
			arg.setName(_args[i++]);
		}

		//insert the function into the context
		c->getScope()->addFunction(_name, func);

		return func;
	}
}