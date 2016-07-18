#include "olac.h"
#include "ArgumentNames.h"
#include "defines.h"

namespace olac {
    Olac::Olac() {
        createArgumentRules();
    }

void Olac::run() {
        //first, check if the required parameters are present
        if (!_arguments.checkValidity())
            return;

        //open the file stream
        _inputFileStream.open(_arguments.getArgumentValue(INPUT_FILE));
        COMPILER_ASSERT_WITH_RETURN(_inputFileStream.is_open(), "Failed opening input-file " << _arguments.getArgumentValue(INPUT_FILE) << ".");

        //set the callback and compile
        _compiler.setCallback(std::bind(&Olac::olaCompilerInputCallback, this));
        while (!_inputFileStream.eof())
            _compiler.compileProgram();

        //close the input
        _inputFileStream.close();
    }

    void Olac::addArguments(int count, char** args) {
        _arguments.parseArguments(count, args);
    }

    void Olac::createArgumentRules() {
        _arguments.registerArgumentExpansion("o", OUTPUT_FILE);
        _arguments.registerArgumentExpansion("i", INPUT_FILE);

        _arguments.registerArgumentType(OUTPUT_FILE, ArgumentType::Value);
        _arguments.registerArgumentType(INPUT_FILE, ArgumentType::Value);

        _arguments.registerRequiredArgument(OUTPUT_FILE);
        _arguments.registerRequiredArgument(INPUT_FILE);
    }

    std::string Olac::olaCompilerInputCallback() {
        char buffer[513];
        _inputFileStream.getline(buffer, 512);

        return std::string(buffer);
    }
}

int main(int argc, char** argv)
{
    //create the compiler wrapper
    olac::Olac olac;
    olac.addArguments(argc-1, argv+1);

    //and let it run
    olac.run();
}
