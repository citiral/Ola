//
// Created by Citiral on 16/09/2015.
//

#ifndef OLA_DASTASSERT_H_H
#define OLA_DASTASSERT_H_H

#include <iostream>

#define DAST_ERROR(message) \
{\
    std::cout << "Error: " << message << "\n";\
}

#define DAST_TODO(message) \
{\
    std::cout << "TODO at " << __FILE__ << "[" << __LINE__ << "]: " << message << "\n";\
    return nullptr;\
}

#define DAST_ASSERT(condition, message) \
{\
    if (!(condition)) {\
        DAST_ERROR(message);\
    }\
}

#endif //OLA_DASTASSERT_H_H
