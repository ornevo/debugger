//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_EXITCOMMAND_H
#define DEBUGGER_EXITCOMMAND_H

#include "Command.h"


class ExitCommand : public Command
{
public:
    ExitCommand();
    virtual bool execute() {};
};


#endif //DEBUGGER_EXITCOMMAND_H
