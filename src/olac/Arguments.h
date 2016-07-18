//
// Created by Citiral on 8/11/2015.
//

#ifndef OLA_ARGUMENTS_H
#define OLA_ARGUMENTS_H

#include <string>
#include <unordered_map>
#include <forward_list>
#include <vector>
#include "types.h"

namespace olac {

    enum class ArgumentType {
        Flag,
        Value,
    };

    class Arguments {
    public:
        Arguments();

        void parseArguments(int count, char** args);

        std::string getArgumentValue(std::string name);
        std::string getArgumentlessValue(u32 index);
        bool argumentValueEquals(std::string name, std::string value);
        bool argumentlessValueEquals(u32 index, std::string value);
        u32 getArgumentlessValuesCount();

        //checks if all required arguments are present
        bool checkValidity();

        void registerArgumentType(std::string name, ArgumentType type);
        void registerArgumentExpansion(std::string shortname, std::string longname);
        void registerRequiredArgument(std::string name);

    private:
        std::unordered_map<std::string, std::string> _argumentExpansions;
        std::unordered_map<std::string, ArgumentType> _argumentTypes;
        std::unordered_map<std::string, std::string> _argumentValues;
        std::forward_list<std::string> _requiredArguments;
        std::vector<std::string> _argumentlessValues;
    };
}

#endif //OLA_ARGUMENTS_H
