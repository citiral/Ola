#include "ola.h"
#include "astassert.h"
#include "passes/LogPass.h"
#include "passes/TypePass.h"
#include "passes/CodegenPass.h"

namespace ola {

    OlaToLlvmCompiler::OlaToLlvmCompiler()
    {

    }

    OlaToLlvmCompiler::~OlaToLlvmCompiler()
    {

    }

    void OlaToLlvmCompiler::compileProgram() {
        //first, lex the program
        auto root = lexProgram();

        //run all passes
        TypePass typePass(_c);
        runPass(root, typePass);

        CodegenPass codegenPass(_c);
        runPass(root, codegenPass);

        LogPass logPass(std::cout);
        runPass(root, logPass);

        //apend the new ast to the current root
        for (auto& elem : root)
            _root.push_back(std::move(elem));
    }

    void OlaToLlvmCompiler::runPass(std::vector<std::unique_ptr<ASTNode>>& nodes, AbstractPass& pass) {
        for (u32 i = 0 ; i < nodes.size() ; i++) {
            if (nodes[i] != nullptr)
                nodes[i]->visit(pass);
        }
    }

    std::vector<std::unique_ptr<ASTNode>> OlaToLlvmCompiler::lexProgram() {
        //get the first token
        _lexer.nextToken();

        //first, generate the AST
        std::vector<std::unique_ptr<ASTNode>> astRoot;

        //keep looping untill we are out of tokens
        do {
            //try to delegate the token to the correct compile function
            switch (_lexer.curToken()) {
                case Token::Eof:
                    return std::move(astRoot);
                default:
                    auto elem = compileBlock();
                    astRoot.push_back(std::move(elem));
                    break;
            }
        } while (!_lexer.atEndOfBuffer());

        return std::move(astRoot);
    }

    std::unique_ptr<ASTNode> OlaToLlvmCompiler::compileBlock() {
        switch (_lexer.curToken()) {
            case Token::Function: {
                auto f = FunctionAST::generate(_lexer);
                return std::move(f);
            } default:
                //return nullptr;
                COMPILE_GENERATE_AND_RETURN_ERROR(_lexer, "Unknown token in block: " << (i32)_lexer.curToken());
        }
    }

    void OlaToLlvmCompiler::setCallback(std::function<std::string()> inputCallback) {
        _lexer.setCallback(std::move(inputCallback));
    }

    Context* OlaToLlvmCompiler::getContext() {
        return &_c;
    }
}