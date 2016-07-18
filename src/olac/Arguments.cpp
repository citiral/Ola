//
// Created by Citiral on 8/11/2015.
//

#include "Arguments.h"
#include "defines.h"

namespace olac {

    Arguments::Arguments() {

    }

    void Arguments::parseArguments(int count, char** args) {
        //loop over each argument
        for (int i = 0 ; i < count ; i++)
        {
            //get the name of the argument
            std::string name = args[i];

            //if the argument starts with '--', remove the dashes
            if (name[0] == '-' && name[1] == '-') {
                name = name.substr(2, std::string::npos);
            }//if the argument starts with '-', remove the dash and expand it
            else if (name[0] == '-' && name[1] != '-') {
                //remove the dashes from the name
                name = name.substr(1, std::string::npos);
                //if it has an expansion, expand it
                auto expansion = _argumentExpansions.find(name);
                if (expansion != _argumentExpansions.end())
                    name = expansion->second;
            }//if the argument doesn't start with '-', it is an argumentless value
            else if (name[0] != '-') {
                _argumentlessValues.push_back(name);
                continue;
            }

            //now look up the type of the argument
            auto typeIter = _argumentTypes.find(name);

            //if it has no type, throw a warning and skip it
            if (typeIter == _argumentTypes.end()) {
                WARNING("Unknown argument " << name);
                continue;
            }

            //get the actual type value
            ArgumentType type = typeIter->second;

            switch (type) {
                case ArgumentType::Flag:
                    _argumentValues[name] = "true";
                    break;
                case ArgumentType::Value:
                    //if this is the last argument, throw a warning
                    if (i == count - 1) {
                        WARNING("Expected value after argument " << name);
                        continue;
                    }
                    _argumentValues[name] = args[i+1];
                    i++;
                    break;
            }
        }
    }

    std::string Arguments::getArgumentValue(std::string name) {
        return _argumentValues[name];
    }

    std::string Arguments::getArgumentlessValue(u32 index) {
        return _argumentlessValues[index];
    }

    bool Arguments::argumentValueEquals(std::string name, std::string value) {
        return _argumentValues[name].compare(value) == 0;
    }

    bool Arguments::argumentlessValueEquals(u32 index, std::string value) {
        return _argumentlessValues[index].compare(value) == 0;
    }

    u32 Arguments::getArgumentlessValuesCount() {
        return _argumentlessValues.size();
    }

    void Arguments::registerArgumentType(std::string name, ArgumentType type) {
        _argumentTypes[name] = type;
    }

    void Arguments::registerArgumentExpansion(std::string shortname, std::string longname) {
        _argumentExpansions[shortname] = longname;
    }

    void Arguments::registerRequiredArgument(std::string name) {
        _requiredArguments.push_front(name);
    }

    bool Arguments::checkValidity() {
        bool validity = true;
        //for each required argument
        for (std::string& name : _requiredArguments) {
            //if there is no value for it, set the validity to false and throw a warning about the missing argument
            if (_argumentValues.find(name) == _argumentValues.end()) {
                validity = false;
                WARNING("Missing required argument " << name);
            }
        }
        return validity;
    }
}