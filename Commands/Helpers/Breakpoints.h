//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_BREAKPOINTS_H
#define DEBUGGER_BREAKPOINTS_H

#include <vector>
#include <cstdint>

#define INT3_OPCODE 0xcc

using namespace std;


typedef struct Breakpoint {
    intptr_t address;
    uint8_t previous_command; // The command that was before the int 3 patch
} Breakpoint;

class Breakpoints {
public:
    static void addBreakpoint(intptr_t address);
    static void removeBreakpoint(intptr_t address);
    static vector<Breakpoint> getBreakpoints();

private:
    static vector<Breakpoint> breakpoints;

    static vector<Breakpoint>::iterator getBreakpointIter(intptr_t address);
};


#endif //DEBUGGER_BREAKPOINTS_H
