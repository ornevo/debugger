//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_BREAKLISTCOMMAND_H
#define DEBUGGER_BREAKLISTCOMMAND_H

#include "Command.h"

#define COMMAND "break-list"


class BreakListCommand : public Command {
public:
    BreakListCommand();
    virtual bool execute();
};


#endif //DEBUGGER_BREAKLISTCOMMAND_H
