//
// Created by citiral on 9/23/15.
//

#ifndef OLA_FUNCTIONPROTOTYPEDAST_H
#define OLA_FUNCTIONPROTOTYPEDAST_H

#include "DASTNode.h"
#include "../type/Type.h"
#include <string>
#include <vector>


namespace ola {

	class FunctionPrototypeDAST : public DASTNode {
	public:
		FunctionPrototypeDAST(DastContext& context, std::string name, std::string type, std::vector<std::string> args);

		Type* getType();

	private:
		Type* _type;
		std::string _name;

		std::vector<std::string> _args;
		std::vector<Type*> _types;
	};

}


#endif //OLA_FUNCTIONPROTOTYPEDAST_H
