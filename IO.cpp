//
// Created by ororor012 on 09/11/18.
//

#include "IO.h"
#include "cpp-linenoise/linenoise.hpp"
#include <boost/algorithm/string.hpp>


bool IO::did_init = false;

void IO::init()
{
    IO::did_init = true;
    if(!linenoise::LoadHistory(SAVED_HISTORY_PATH))
        cout << "Failed to load command line history." << endl;
}

void IO::destruct()
{
    if(!linenoise::SaveHistory(SAVED_HISTORY_PATH))
        cout << "Failed to save command line history." << endl;
}

vector<string> IO::nextCommand()
{
    if(!IO::did_init)
        throw "IO WAS NOT INITIALIZED";

    string line;
    linenoise::Readline(PROMPT, line);
    linenoise::AddHistory(line.c_str());

    vector<string> splitted;
    boost::split(splitted, line, [](char curr) { return curr == ' '; });
    vector<string> ret(splitted.begin(),
                       remove_if(splitted.begin(), splitted.end(), [](const string& curr) { return curr.empty(); }));

    return ret;
}