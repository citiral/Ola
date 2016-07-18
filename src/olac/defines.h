//
// Created by Citiral on 8/11/2015.
//

#ifndef OLAC_DEFINES_H
#define OLAC_DEFINES_H

#include <iostream>

#define WARNING(x) std::cout << "Warning: " << x << "\n"

#define COMPILER_ASSERT_WITH_RETURN(condition, message)\
{\
    if (!(condition)) {\
        WARNING(message);\
        return;\
    }\
}

#endif //OLA_DEFINES_H
