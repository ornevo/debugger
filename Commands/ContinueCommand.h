//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_CONTINUECOMMAND_H
#define DEBUGGER_CONTINUECOMMAND_H


#include "Command.h"

class ContinueCommand : public Command
{
public:
    ContinueCommand();
    bool execute();
};


#endif //DEBUGGER_CONTINUECOMMAND_H
