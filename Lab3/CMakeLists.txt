cmake_minimum_required(VERSION 3.17)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab3 main.cpp Predicate.h Token.h Scanner.h Parser.h Parameter.h Rule.h DatalogProgram.h Scheme.h Tuple.h Relation.h Database.h Interpreter.h)