# cmake_minimum_required(VERSION <specify CMake version here>)
project(MiniJavaCompiler)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-5")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -ansi -pedantic -std=c++11")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" )

SET(PARSER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Parser")
SET(PARSER_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Output")
SET(PARSER_NODES_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/Nodes")

SET(BisonOutput ${PARSER_OUTPUT_DIR}/parser.cpp)
SET(BISON_EXECUTABLE /usr/bin/bison)

ADD_CUSTOM_COMMAND(
        OUTPUT ${BisonOutput}
        COMMAND ${BISON_EXECUTABLE}
            --defines=${PARSER_SOURCE_DIR}/heading.h
            --output=${BisonOutput}
        ${PARSER_SOURCE_DIR}/bison.y
        COMMENT "Generating parser.cpp"
    )

SET(FlexOutput ${PARSER_OUTPUT_DIR}/lexer.cpp)
SET(FLEX_EXECUTABLE /usr/bin/flex)

ADD_CUSTOM_COMMAND(
        OUTPUT ${FlexOutput}
        COMMAND ${FLEX_EXECUTABLE}
            --outfile=${FlexOutput}
        ${PARSER_SOURCE_DIR}/flex.l
        COMMENT "Generating lexer.cpp"
)

file(GLOB NodeList ${PARSER_NODES_DIR} "${PARSER_NODES_DIR}/*.cpp")

INCLUDE_DIRECTORIES(${PARSER_SOURCE_DIR} ${PARSER_NODES_DIR})

add_executable(MiniJavaCompiler ${NodeList} ${BisonOutput} ${FlexOutput} ${PARSER_SOURCE_DIR}/main.cc)