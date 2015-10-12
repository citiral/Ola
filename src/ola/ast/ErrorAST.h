//
// Created by citiral on 10/6/15.
//

#ifndef OLA_ERRORAST_H
#define OLA_ERRORAST_H

#include "ASTNode.h"

namespace ola {

	class ErrorAST : public ASTNode {
		AST_NODE
	public:
		ErrorAST(Lexer& l, std::string error);

	private:
		std::string _error;
	};

}

#endif //OLA_ERRORAST_H
