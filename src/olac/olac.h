//
// Created by Citiral on 8/11/2015.
//

#include "Arguments.h"
#include "ola.h"
#include <fstream>

#ifndef OLA_OLAC_H
#define OLA_OLAC_H

namespace olac {
    class Olac {
    public:
        Olac();

        //runs the compiler
        void run();

        //adds arguments to the compiler
        void addArguments(int count, char** args);

    private:
        //creates the argument rules
        void createArgumentRules();

        //callback for the ola compiler to fetch more input
        std::string olaCompilerInputCallback();

        //opens the input file to compile


        Arguments _arguments;
        ola::OlaToLlvmCompiler _compiler;
        std::ifstream _inputFileStream;
        std::ofstream _outputFileStream;
    };
}

#endif //OLA_OLAC_H
