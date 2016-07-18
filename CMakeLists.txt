cmake_minimum_required (VERSION 3.3)
project (ola)

#setting up cmake variables for all projects
SET (CC clang)
SET (CXX clang++)

set (CXX_FLAGS "-std=c++11 -Wall -Werror=return-type")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")


find_package(LLVM REQUIRED CONFIG)

message("Found LLVM ${LLVM_PACKAGE_VERSION}")
message("Using LLVMConfig.cmake in: ${LLVM_DIR}")
message("llvm include dir is : ${LLVM_INCLUDE_DIRS}")
message("llvm def dir is : ${LLVM_DEFINITIONS}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader)

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
		${PROJECT_SOURCE_DIR}/src/ola/ast/FunctionPrototypeAST.cpp
		src/ola/ast/FunctionPrototypeAST.h src/ola/ast/FunctionAST.cpp src/ola/ast/FunctionAST.h src/ola/astassert.h
		src/ola/ast/ExpressionKillerAST.cpp src/ola/ast/ExpressionKillerAST.h src/ola/ast/FunctionCallAST.cpp src/ola/ast/FunctionCallAST.h
		src/ola/type/Type.h src/ola/type/TypeList.cpp src/ola/type/TypeList.h src/ola/type/PrimitiveType.cpp src/ola/type/PrimitiveType.h
		src/ola/passes/TypePass.cpp src/ola/passes/TypePass.h src/ola/passes/Context.cpp src/ola/passes/Context.h src/ola/adt/StackMap.h
		src/ola/passes/LogPass.cpp src/ola/passes/LogPass.h src/ola/passes/AbstractPass.cpp src/ola/passes/AbstractPass.h src/ola/passes/CodegenPass.cpp
		src/ola/passes/CodegenPass.h src/ola/passes/AbstractStackPass.cpp src/ola/passes/AbstractStackPass.h src/ola/defines.h src/ola/ast/ErrorAST.cpp src/ola/ast/ErrorAST.h)

target_link_libraries(ola ${llvm_libs})

#an ola-front end resembling a shell. depends on ola
add_executable (olash
	${PROJECT_SOURCE_DIR}/src/olash/olash.cpp
	${PROJECT_SOURCE_DIR}/src/olash/shell.cpp
)

add_executable(olac
        ${PROJECT_SOURCE_DIR}/src/olac/olac.cpp
        src/olac/Arguments.cpp src/olac/Arguments.h src/olac/defines.h src/olac/olac.h src/olac/ArgumentNames.h)

target_link_libraries (olash ola)
target_link_libraries (olac ola)

set_property (TARGET olash PROPERTY INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/ola/ ${LLVM_INCLUDE_DIRS})
set_property (TARGET olac PROPERTY INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/ola/ ${LLVM_INCLUDE_DIRS})