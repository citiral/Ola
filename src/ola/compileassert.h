//
// Created by citiral on 9/8/15.
//

#ifndef OLA_COMPILEASSERT_H
#define OLA_COMPILEASSERT_H

#define COMPILE_GENERATE_AND_RETURN_ERROR(lex, message) \
{\
    std::cout << "Error: " << message << "\n";\
    lex.nextToken();\
    return nullptr;\
}

#define COMPILE_GENERATE_AND_RETURN_TODO(lex, message) \
{\
    std::cout << "TODO at " << __FILE__ << "[" << __LINE__ << "]: " << message << "\n";\
    lex.nextToken();\
    return nullptr;\
}

#define COMPILE_RETURN_ERROR(message) \
{\
    std::cout << "Error: " << message << "\n";\
    return nullptr;\
}

#define COMPILE_ASSERT(condition, message) \
{\
    if (!(condition)) {\
        COMPILE_RETURN_ERROR(message);\
    }\
}


#endif //OLA_COMPILEASSERT_H
