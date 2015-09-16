//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_TYPELIST_H
#define OLA_TYPELIST_H

#include "Type.h"
#include <string>
#include <memory>
#include <map>

namespace ola {

    /**
     * This class manages a list of all types, and can be used to create new types.
     * Types are all managed by the typelist.
     */
    class TypeList {
    public:
        TypeList();
        bool hasType(std::string name);
        Type* getType(std::string name);

    private:
        void insertType(std::string name, std::unique_ptr<Type> _type);
        void definePrimitiveTypes();

        std::map<std::string, std::unique_ptr<Type> > _types;
    };

}


#endif //OLA_TYPELIST_H
