//
// Created by ororor012 on 09/11/18.
//

#include <sys/ptrace.h>
#include <algorithm>
#include <iostream>
#include "Breakpoints.h"
#include "../../Debugger.h"


vector<Breakpoint> Breakpoints::breakpoints({});

void Breakpoints::addBreakpoint(intptr_t address) {
    Debugger& dbg = Debugger::get();
    Breakpoint to_add;

    if(getBreakpointIter(address) != breakpoints.end())
    {
        cout << "Breakpoint already set" << endl;
        return;
    }

    auto previous_data = ptrace(PTRACE_PEEKDATA, dbg.getChildPID(), address, nullptr);
    if(previous_data == -1)
    {
        cout << "Failed to read address 0x" << hex << address << ": " << strerror(errno) << endl;
        return;
    }

    to_add.previous_command = static_cast<uint8_t>(previous_data);
    to_add.address = address;

    uint64_t patched_int3_data = (previous_data & ~0xff) | INT3_OPCODE;
    if(ptrace(PTRACE_POKEDATA, dbg.getChildPID(), address, patched_int3_data) == -1)
    {
        cout << "Failed to set breakpoint at 0x" << hex << address << ": " << strerror(errno) << endl;
        return;
    }

    Breakpoints::breakpoints.push_back(to_add);
}


void Breakpoints::removeBreakpoint(intptr_t address) {
    auto brk = getBreakpointIter(address);
    if(brk == breakpoints.end())
    {
        cout << "No breakpoint set at 0x" << hex << address << "." << endl;
        return;
    }

    Breakpoint removed = *brk;
    breakpoints.erase(brk);

    // After removed internally, remove from debgged process
    ptrace(PTRACE_POKEDATA, Debugger::get().getChildPID(), address, removed.previous_command);
}


vector<Breakpoint> Breakpoints::getBreakpoints() {
    return breakpoints;
}

/* Private helpers */

vector<Breakpoint>::iterator Breakpoints::getBreakpointIter(intptr_t address) {
    return find_if(breakpoints.begin(), breakpoints.end(), [&](const Breakpoint& brk) {
        return brk.address == address;
    });
}
