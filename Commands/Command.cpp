//
// Created by ororor012 on 09/11/18.
//

#include "Command.h"


bool Command::doesMatch(const vector<string> &line)
{
    return this->params.load(line);
}

Command::Command(const vector<PARAM_TYPES> &params_template, const string &command_name)
        : params(params_template, command_name), command_name(command_name) {}
