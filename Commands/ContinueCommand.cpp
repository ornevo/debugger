//
// Created by ororor012 on 09/11/18.
//

#include <sys/ptrace.h>
#include <wait.h>
#include <iostream>
#include <bits/siginfo.h>
#include "ContinueCommand.h"
#include "../Debugger.h"


ContinueCommand::ContinueCommand() : Command(vector<PARAM_TYPES>({}), "continue") {}

bool ContinueCommand::execute() {
    Debugger& dbg = Debugger::get();

    ptrace(PTRACE_CONT, dbg.getChildPID(), nullptr, nullptr);

    siginfo_t received_signal = dbg.child_waitpid();
    switch(received_signal.si_code)
    {
        case CLD_EXITED:
            cout << "Child process exited with status " << received_signal.si_status << endl;
            break;
        case CLD_KILLED:
            cout << "Child process killed and exited with status " << received_signal.si_status << endl;
            break;
    }

    return true;
}
