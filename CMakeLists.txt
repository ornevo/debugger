cmake_minimum_required(VERSION 3.9)
project(debugger)

set(CMAKE_CXX_STANDARD 11)

add_executable(debugger main.cpp Debugger.cpp Debugger.h IO.cpp IO.h Commands/Command.h Commands/ExitCommand.cpp Commands/ExitCommand.h Commands/Helpers/ParamParser.cpp Commands/Helpers/ParamParser.h Commands/Command.cpp)