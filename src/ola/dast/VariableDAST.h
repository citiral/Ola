//
// Created by citiral on 9/23/15.
//

#ifndef OLA_VARIABLEDAST_H
#define OLA_VARIABLEDAST_H

#include "../dast/ExpressionDAST.h"
#include <llvm/IR/Value.h>
#include "../codegen/Context.h"
#include "../codegenassert.h"

namespace ola {

class VariableDAST : public ExpressionDAST {
public:
	VariableDAST(DastContext& dc, std::string name);
	Type* getType() override;
	virtual llvm::Value* codegen(Context* c) override;

private:
	Type* _type;
	std::string _name;
};

}

#endif //OLA_VARIABLEDAST_H
