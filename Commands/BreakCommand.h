//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_BREAKCOMMAND_H
#define DEBUGGER_BREAKCOMMAND_H

#include "Command.h"

#define SUBC_SET "set"
#define SUBC_REMOVE "remove"

class BreakCommand : public Command {
public:
    BreakCommand();
    virtual bool execute();
};


#endif //DEBUGGER_BREAKCOMMAND_H
