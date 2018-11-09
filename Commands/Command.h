//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_COMMAND_H
#define DEBUGGER_COMMAND_H

#include <string>
#include <vector>
#include "Helpers/ParamParser.h"

using namespace std;


class Command {
public:
    Command(const vector<PARAM_TYPES>& params_template, const string& command_name);
    virtual bool doesMatch(const vector<string>& line);
    // Return if success or not.
    virtual bool execute(const vector<string>& line) = 0;

protected:
    string command_name;
    ParamParser params;
};


#endif //DEBUGGER_COMMAND_H
