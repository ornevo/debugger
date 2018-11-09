//
// Created by ororor012 on 08/11/18.
//

#ifndef DEBUGGER_DEBUGGER_H
#define DEBUGGER_DEBUGGER_H

#include <string>

using namespace std;


class Debugger {
public:
    Debugger(const string& prog_name_param, pid_t traced_pid) :
            prog_name(prog_name_param), child_pid(traced_pid) {}

    void run();

private:
    string prog_name;
    pid_t child_pid;

    void handle_command(string basic_string);
};


#endif //DEBUGGER_DEBUGGER_H
