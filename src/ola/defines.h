//
// Created by citiral on 10/5/15.
//

#ifndef OLA_DEFINES_H
#define OLA_DEFINES_H

#include <iostream>
#include <assert.h>

#define DEBUG

#ifdef DEBUG

#define COMPILER_ASSERT(condition, message) \
{\
	if (!(condition)) {\
		COMPILER_ERROR(message)\
	}\
}\

#define COMPILER_ERROR(message)\
{\
	std::cout << "Compiler error at " << __FILE__ << "[" << __LINE__ << "]: " << message << "\n";\
	assert(false);\
}\

#else

#define COMPILER_ASSERT(condition, message)
#define COMPILER_ERROR(message)

#endif

#endif //OLA_DEFINES_H
