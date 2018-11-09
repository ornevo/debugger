//
// Created by ororor012 on 08/11/18.
//

#include <memory>
#include "Debugger.h"
#include "cpp-linenoise/linenoise.hpp"
#include "IO.h"
#include "Commands/ExitCommand.h"
#include "Commands/ContinueCommand.h"
#include "Commands/BreakCommand.h"
#include "Commands/BreakListCommand.h"


bool Debugger::current_command_found = false;

const vector<Command*> Debugger::commands({
  new ContinueCommand,
  new BreakCommand,
  new BreakListCommand
});

void Debugger::run()
{
    int wait_status;
    // Send a SIGTRAP signal to the debugged process
    waitpid(this->child_pid, &wait_status, 0);

    ExitCommand exit;
    while(true)
    {
        auto line = IO::nextCommand();
        if(line.empty())
            continue;

        if(exit.doesMatch(line))
            break;

        Debugger::current_command_found = false;
        for(auto const& comm : Debugger::commands)
            if(comm->doesMatch(line))
            {
                comm->execute();
                break;
            }

        if(!Debugger::current_command_found)
            cout << "\"" << line[0] << "\" is not a command." << endl;
    }

    cout << "Bye!" << endl;

    for(auto comm_ptr : Debugger::commands)
        delete comm_ptr;
}

void Debugger::handle_command(string command)
{
    if(command == "exit")
        exit(0);
    else
        cout << "Unknown Command" << endl;
}

__pid_t Debugger::getChildPID() {
    return this->child_pid;
}

void Debugger::notifyMatchedCommand() {
    Debugger::current_command_found = true;
}

siginfo_t Debugger::child_waitpid() {
    siginfo_t siginfo;
    waitid(P_PID, this->child_pid, &siginfo, WEXITED | WSTOPPED | WCONTINUED);

    return siginfo;
}

void Debugger::killChild() {
    kill(this->child_pid, 9);
}


/* Singleton things */

Debugger& Debugger::get(const string &prog_name_param, __pid_t traced_pid) {
    static bool initialized = false;
    // If prog_name_param is empty, it means it got called from the overloading
    //  get() function begore initialization
    if(prog_name_param.empty() && !initialized)
        throw invalid_argument("Tried to get instance before instance got initialized.");
    initialized = true;

    static Debugger instance(prog_name_param, traced_pid);

    return instance;
}

Debugger& Debugger::get() {
    return get("", -1);
}

