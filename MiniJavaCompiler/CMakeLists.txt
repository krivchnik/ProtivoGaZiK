# cmake_minimum_required(VERSION <specify CMake version here>)
project(MiniJavaCompiler)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-5")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -ansi -pedantic -std=c++11")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" )

#[[# Create target for the parser
ADD_CUSTOM_TARGET(Compiler echo "Creating parser.c")

# Create custom command for flex/lex (note the outputs)
ADD_CUSTOM_COMMAND(
        SOURCE ${PARSER_SOURCE_DIR}/flex.l
        COMMAND /usr/bin/flex
        ARGS -o ${PARSER_OUTPUT_DIR}/lexer.c ${PARSER_SOURCE_DIR}/flex.l
        TARGET Compiler
        OUTPUTS ${PARSER_OUTPUT_DIR}/lexer.c)

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
        SOURCE ${PARSER_SOURCE_DIR}/bison.y
        COMMAND /usr/bin/bison
        ARGS -y ${PARSER_SOURCE_DIR}/bison.y
        -o ${PARSER_OUTPUT_DIR}/parser.c
        TARGET Compiler
        #DEPENDS ${PARSER_OUTPUT_DIR}/lexer.c
        OUTPUTS ${PARSER_OUTPUT_DIR}/parser.c)

# Add parser.c to the list of sources
SET(COMPILER_SOURCES ${COMPILER_SOURCES} ${PARSER_OUTPUT_DIR}/parser.c ${PARSER_OUTPUT_DIR}/lexer.c ${PARSER_SOURCE_DIR}/main.cc)

# Since parser.c does not exists yet when cmake is run, mark
# it as generated
SET_SOURCE_FILES_PROPERTIES(${PARSER_OUTPUT_DIR}/parser.c GENERATED)
SET_SOURCE_FILES_PROPERTIES(${PARSER_OUTPUT_DIR}/lexer.c GENERATED)

# Include binary directory to include lexer.c in parser.c
INCLUDE_DIRECTORIES(${PARSER_SOURCE_DIR})

add_executable(MiniJavaCompiler ${COMPILER_SOURCES})]]

SET(PARSER_SOURCE_DIR "/home/nismohl/ClionProjects/MiniJavaCompiler/Parser")
SET(PARSER_OUTPUT_DIR "/home/nismohl/ClionProjects/MiniJavaCompiler/Output")
SET(PARSER_NODES_DIR  "/home/nismohl/ClionProjects/MiniJavaCompiler/Nodes")

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

MESSAGE( STATUS "CMAKE_CURRENT_BISON_OUPTUT: " ${BisonOutput} )

file(GLOB NodeList ${PARSER_NODES_DIR} "${PARSER_NODES_DIR}/*.cpp")

MESSAGE( STATUS "CMAKE_CURRENT_NODES_OUPTUT: " ${Nodes})

INCLUDE_DIRECTORIES(${PARSER_SOURCE_DIR} ${PARSER_NODES_DIR})

add_executable(MiniJavaCompiler ${NodeList} ${BisonOutput} ${FlexOutput} ${PARSER_SOURCE_DIR}/main.cc)