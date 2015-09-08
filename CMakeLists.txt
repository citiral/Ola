cmake_minimum_required (VERSION 3.3)
project (ola)

#setting up cmake variables for all projects
SET (CC clang)
SET (CXX clang++)

set (CXX_FLAGS "-std=c++14 -Wall -Werror=return-type")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")


find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#the ola back-end
add_library (ola SHARED
		${PROJECT_SOURCE_DIR}/src/ola/ola.cpp
		${PROJECT_SOURCE_DIR}/src/ola/lexer.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast.h
		${PROJECT_SOURCE_DIR}/src/ola/types.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/ASTNode.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast/ASTNode.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/ExpressionAST.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast/ExpressionAST.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/ExpressionSeriesAST.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast/ExpressionSeriesAST.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/NumberIntegerAST.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast/NumberIntegerAST.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/VariableAST.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast/VariableAST.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/BinaryOperatorAST.cpp
		${PROJECT_SOURCE_DIR}/src/ola/ast/BinaryOperatorAST.h
		${PROJECT_SOURCE_DIR}/src/ola/ast/FunctionPrototypeAST.cpp src/ola/ast/FunctionPrototypeAST.h src/ola/ast/FunctionAST.cpp src/ola/ast/FunctionAST.h src/ola/compileassert.h src/ola/ast/ExpressionKillerAST.cpp src/ola/ast/ExpressionKillerAST.h)

#an ola-front end resembling a shell. depends on ola
add_executable (olash
	${PROJECT_SOURCE_DIR}/src/olash/olash.cpp
	${PROJECT_SOURCE_DIR}/src/olash/shell.cpp
)
target_link_libraries (olash ola)
set_property (TARGET olash PROPERTY INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/ola/)