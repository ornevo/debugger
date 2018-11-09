//
// Created by ororor012 on 08/11/18.
//

#ifndef DEBUGGER_DEBUGGER_H
#define DEBUGGER_DEBUGGER_H

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "Commands/Command.h"

using namespace std;


class Debugger {
public:
    Debugger(const string& prog_name_param, __pid_t traced_pid) :
             prog_name(prog_name_param), child_pid(traced_pid) {}

    void run();
    __pid_t getChildPID();
    siginfo_t child_waitpid();
    void killChild();

    // Make it a singleton pattern
    static Debugger& get();
    static Debugger& get(const string& prog_name_param, __pid_t traced_pid);
    static void notifyMatchedCommand();

private:
    string prog_name;
    __pid_t child_pid;

    static bool current_command_found;

    void handle_command(string basic_string);
    static const vector<Command *> commands;
};


#endif //DEBUGGER_DEBUGGER_H
