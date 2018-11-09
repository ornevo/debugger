//
// Created by ororor012 on 09/11/18.
//

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "ParamParser.h"
#include "../../Debugger.h"


ParamParser::ParamParser(const vector<PARAM_TYPES> &structure, const string &command_name)
        : structure(structure), command_name(command_name) {}

bool ParamParser::load(const vector<string> &line) {
    this->current_line = line;
    // Base cases, where nothing should get printed
    if(line.empty()) return false;
    if(line[0] != this->command_name) return false;

    Debugger::notifyMatchedCommand();

    // If good command name, but bad number of args
    if(line.size() - 1 != this->structure.size())
    {
        cout << "Bad command usage." << endl;
        this->printUsage();
        return false;
    }

    for (int i = 0; i < this->structure.size(); ++i)
    {
        PARAM_TYPES type = this->structure[i];
        const string& param = line[i+1];
        switch (type)
        {
            case PARAM_TYPES::NUMBER:
                if(!ParamParser::matchNumber(param))
                {
                    cout << "Bad number at argument number " << i+1 << endl;
                    printUsage();
                    return false;
                }
                break;
            case PARAM_TYPES::ADDRESS:
                if(!ParamParser::matchAddress(param))
                {
                    cout << "Bad address at argument number " << i+1 << endl;
                    printUsage();
                    return false;
                }
                break;
        }
    }

    return true;
}

bool ParamParser::matchNumber(const string &val) {
    string to_check = move(val);
    // Remove a minus if present
    if(to_check[0] == '-')
        to_check = to_check.substr(1);
    return find_if(to_check.begin(), to_check.end(), [](const char& c){ return c < '0' || c > '9'; }) == to_check.end();
}

bool ParamParser::matchAddress(const string &val) {
    // Try to convert hex number
    try
    {
        auto add = boost::lexical_cast<uint64_t>(val);
    }
    catch(boost::bad_lexical_cast &)
    {
        return false;
    }

    return true;
}

void ParamParser::printUsage() {
    cout << "Usage: " << this->command_name;
    for(auto type : this->structure)
        switch (type)
        {
            case PARAM_TYPES::STRING:
                cout << " <STRING>";
                break;
            case PARAM_TYPES ::NUMBER:
                cout << " <NUMBER>";
                break;
            case PARAM_TYPES ::ADDRESS:
                cout << " <ADDRESS>";
                break;
        }
    cout << endl;
}

template <typename RetType>
unique_ptr<void> ParamParser::operator[](int index) {
    if(index < 0 || index > this->structure.size())
        throw out_of_range("Index " + to_string(index) + " is out parameters bounds.");

    string param = this->current_line[index+1];
    switch(this->structure[index])
    {
        case PARAM_TYPES::NUMBER:
            return unique_ptr<RetType>(new int32_t(stoi(param)));
        case PARAM_TYPES ::ADDRESS:
            return unique_ptr<RetType>(new uint64_t(boost::lexical_cast<int64_t>(param)));
        default:
            return unique_ptr<RetType>(new string(param));
    }
}
