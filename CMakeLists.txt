cmake_minimum_required(VERSION 3.9)
project(debugger)

set(CMAKE_CXX_STANDARD 17)

add_executable(debugger main.cpp Debugger.cpp Debugger.h IO.cpp IO.h Commands/Command.h Commands/ExitCommand.cpp Commands/ExitCommand.h Commands/Helpers/ParamParser.cpp Commands/Helpers/ParamParser.h Commands/Command.cpp Commands/ContinueCommand.cpp Commands/ContinueCommand.h Commands/BreakCommand.cpp Commands/BreakCommand.h Commands/Helpers/Breakpoints.cpp Commands/Helpers/Breakpoints.h Commands/BreakListCommand.cpp Commands/BreakListCommand.h)