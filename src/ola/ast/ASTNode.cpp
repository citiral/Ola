//
// Created by citiral on 9/8/15.
//

#include "ASTNode.h"
namespace ola {

	ASTNode::~ASTNode(Lexer& l) {
		_lineNumber = l.getLineNumber();
		_charNumber = l.getCharNumber();
	}

	u32 ASTNode::getLineNumber() {
		return _lineNumber;
	}

	u32 ASTNode::getCharNumber() {
		return _charNumber;
	}
}
