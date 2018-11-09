//
// Created by ororor012 on 09/11/18.
//

#include <iostream>
#include "BreakCommand.h"
#include "Helpers/Breakpoints.h"

BreakCommand::BreakCommand() : Command(
        vector<PARAM_TYPES>({PARAM_TYPES::ENUM, PARAM_TYPES::ADDRESS}), string("break"))
{
    this->params.defineEnum(vector<string>({SUBC_SET, SUBC_REMOVE}));
}

bool BreakCommand::execute() {
    string subcommand = boost::any_cast<string>(params[0]);

    auto address = boost::any_cast<intptr_t>(params[1]);
    if(subcommand == SUBC_SET)
        Breakpoints::addBreakpoint(address);
    else if(subcommand == SUBC_REMOVE)
        Breakpoints::removeBreakpoint(address);
}
