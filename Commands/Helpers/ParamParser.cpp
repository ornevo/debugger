//
// Created by ororor012 on 09/11/18.
//

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "ParamParser.h"
#include "../../Debugger.h"


ParamParser::ParamParser(const vector<PARAM_TYPES> &structure, const string &command_name)
        : structure(structure), command_name(command_name), enums() {}

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

    int enums_count = 0; // Number of enums seen so far
    for (int i = 0; i < this->structure.size(); ++i)
    {
        PARAM_TYPES type = this->structure[i];
        const string& param = line[i+1];
        switch (type)
        {
            case PARAM_TYPES::ENUM:
                if(!this->matchEnum(param, enums_count))
                {
                    cout << "Argument number " << (i+1) << " is not in the argument's allowed values." << endl;
                    printUsage();
                    return false;
                }
                ++enums_count;
                break;
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
                    cout << "Bad address at argument number " << i+1 << ". Must be a hex value starting with \"0x\"." << endl;
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
    if(val.length() < 3 || val.substr(0, 2) != "0x")
        return false;

    for(auto c : val.substr(2))
        if(!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
            return false;

    return true;
}

void ParamParser::printUsage() {
    cout << "Usage: " << this->command_name;
    int enum_i = 0;
    for(auto type : this->structure)
        switch (type)
        {
            case PARAM_TYPES::STRING:
                cout << " <STRING>";
                break;
            case PARAM_TYPES::ENUM:
                cout << enumUsageString(getEnum(enum_i++));
                break;
            case PARAM_TYPES::NUMBER:
                cout << " <NUMBER>";
                break;
            case PARAM_TYPES::ADDRESS:
                cout << " <ADDRESS>";
                break;
        }
    cout << endl;
}

boost::any ParamParser::operator[](int index) {
    if(index < 0 || index > this->structure.size())
        throw out_of_range("Index " + to_string(index) + " is out parameters bounds.");

    string param = this->current_line[index+1];
    switch(this->structure[index])
    {
        case PARAM_TYPES::NUMBER:
            return stoi(param);
        case PARAM_TYPES::ADDRESS:
            return static_cast<int64_t>(strtoul(param.c_str(), nullptr, 16));
        default:
            return string(param);
    }
}

void ParamParser::defineEnum(const vector<string> &allowedValues) {
    this->enums.push_back(move(allowedValues));
}

bool ParamParser::matchEnum(const string &param, int enum_i) {
    auto const& allowed_vals = this->getEnum(enum_i);
    return find(allowed_vals.begin(), allowed_vals.end(), param) != allowed_vals.end();
}

const vector<string> &ParamParser::getEnum(int enum_i) {
    if(enum_i >= this->enums.size())
        throw range_error("More enum parameters than enums defined.");
    return this->enums[enum_i];
}

const string ParamParser::enumUsageString(const vector<string> &enum_vec) {
    string to_print(" <");
    for(auto s : enum_vec)
        to_print.append(s + "|");
    return to_print.substr(0, to_print.length()-1) + ">";
}
