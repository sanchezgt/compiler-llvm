# Minimum CMake required version
cmake_minimum_required(VERSION 3.10)
project(UmbraLang VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


if(MSVC)
  add_compile_options(/W4 /WX)
else()
  #add_compile_options(-Wall -Wextra -Werror)
  add_compile_options(-Wall -Wextra)
endif()

# LLVM package
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})


# The lexer library
add_library(umbra_lexer STATIC
    src/lexer/Lexer.cpp
    src/lexer/Lexer.h
    src/error/CompilerError.cpp
    src/error/ErrorManager.cpp
)



# The Umbra compiler executable
file(GLOB_RECURSE SOURCES 
  "src/main.cpp"  
  "src/parser/*.cpp"  
  "src/lexer/*.cpp" 
  "src/ast/statementnodes/*.cpp"
  "src/ast/expressionnodes/*.cpp"
  "src/ast/visitor/*.cpp"
  "src/error/*.cpp")
add_executable(umbra_compiler ${SOURCES})
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(umbra_compiler ${llvm_libs} umbra_lexer)


# Set output directory
set_target_properties(umbra_compiler
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


# Add tests
include(FetchContent)

# Descargar GoogleTest si no está presente
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Añadir ejecutable de test
add_executable(lexer_test test/lexer_test.cpp)

# Enlazar GoogleTest
target_link_libraries(lexer_test umbra_lexer gtest gtest_main)

# Habilitar la ejecución de tests
add_test(NAME lexer_test COMMAND lexer_test)

# Set output directory
set_target_properties(lexer_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
