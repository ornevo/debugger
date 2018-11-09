//
// Created by ororor012 on 08/11/18.
//

#include <wait.h>
#include "Debugger.h"
#include "cpp-linenoise/linenoise.hpp"
#include "IO.h"
#include "Commands/ExitCommand.h"


void Debugger::run()
{
    int wait_status;
    // Send a SIGTRAP signal to the debugged process
    waitpid(this->child_pid, &wait_status, 0);

    ExitCommand exit;
    while(true)
    {
        auto line = IO::nextCommand();
        if(exit.doesMatch(line))
            break;

    }

    cout << "Bye!" << endl;
}

void Debugger::handle_command(string command)
{
    if(command == "exit")
        exit(0);
    else
        cout << "Unknown Command" << endl;
}
