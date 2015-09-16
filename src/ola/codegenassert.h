//
// Created by citiral on 9/9/15.
//

#ifndef OLA_CODEGENASSERT_H_H
#define OLA_CODEGENASSERT_H_H

#include <iostream>

#define CODEGEN_RETURN_ERROR(message) \
{\
    std::cout << "Error: " << message << "\n";\
    return nullptr;\
}

#define CODEGEN_RETURN_TODO(message) \
{\
    std::cout << "TODO at " << __FILE__ << "[" << __LINE__ << "]: " << message << "\n";\
    return nullptr;\
}

#define CODEGEN_ASSERT(condition, message) \
{\
    if (!(condition)) {\
        CODEGEN_RETURN_ERROR(message);\
    }\
}


#endif //OLA_CODEGENASSERT_H_H
