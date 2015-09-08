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
		src/ola/ast.cpp src/ola/ast.h src/ola/types.h)

#an ola-front end resembling a shell. depends on ola
add_executable (olash
	${PROJECT_SOURCE_DIR}/src/olash/olash.cpp
	${PROJECT_SOURCE_DIR}/src/olash/shell.cpp
)
target_link_libraries (olash ola)
set_property (TARGET olash PROPERTY INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/ola/)