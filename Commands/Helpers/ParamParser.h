//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_PARAMPARSER_H
#define DEBUGGER_PARAMPARSER_H

#include <vector>
#include <string>
#include <memory>
#include <boost/any.hpp>

using namespace std;


enum PARAM_TYPES {
    STRING, // string
    ENUM, // string out of predefined allowed strings. Should be defined with .defineEnum(...)
    NUMBER, // int
    ADDRESS // intptr_t
};


class ParamParser {
public:
    ParamParser(const vector<PARAM_TYPES>& structure, const string& command_name);
    // Returns whether the line matched the structure
    bool load(const vector<string>& line);

    // Declare what values can an enum have
    void defineEnum(const vector<string>& allowedValues);

    // Receives param index
    boost::any operator[](int index);

private:
    vector<PARAM_TYPES> structure;
    string command_name;
    vector<string> current_line;
    vector<vector<string>> enums;

    static bool matchNumber(const string& val);
    static bool matchAddress(const string& val);

    void printUsage();
    const string enumUsageString(const vector<string>& enum_vec);

    // enum_i should be the index in the enums vector (the number of enums before the current)
    const vector<string>& getEnum(int enum_i);
    bool matchEnum(const string &param, int enum_i);
};


#endif //DEBUGGER_PARAMPARSER_H
