//
// Created by ororor012 on 09/11/18.
//

#include <iostream>
#include "BreakListCommand.h"
#include "Helpers/Breakpoints.h"

using namespace std;


BreakListCommand::BreakListCommand() : Command(vector<PARAM_TYPES>({}), COMMAND) {}

bool BreakListCommand::execute() {
    for(auto brk : Breakpoints::getBreakpoints())
        cout << "Breakpoint at 0x" << hex << brk.address << endl;
}
