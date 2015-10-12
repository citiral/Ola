//
// Created by citiral on 10/6/15.
//

#include "ErrorAST.h"

namespace ola {

	ErrorAST::ErrorAST(Lexer& l, std::string error):
			ASTNode(l),
			_error(std::move(error)) {

	}

}
