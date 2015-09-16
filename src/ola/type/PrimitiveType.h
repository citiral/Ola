//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_PRIMITIVETYPE_H
#define OLA_PRIMITIVETYPE_H

#include "Type.h"

namespace ola {
    class PrimitiveType : public Type {
    public:
        PrimitiveType(TypeType primitiveType, std::string name);
        virtual TypeType getType();

        bool equals(Type* t) override;
    private:
        bool equals_handle(PrimitiveType* t) override;

        TypeType _type;
        std::string _name;
    };
}


#endif //OLA_PRIMITIVETYPE_H
