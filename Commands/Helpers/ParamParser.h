//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_PARAMPARSER_H
#define DEBUGGER_PARAMPARSER_H

#include <vector>
#include <string>
#include <memory>

using namespace std;


enum PARAM_TYPES {
    STRING, // string
    NUMBER, // int
    ADDRESS // int64_t
};


class ParamParser {
public:
    ParamParser(const vector<PARAM_TYPES>& structure, const string& command_name);
    // Returns whether the line matched the structure
    bool load(const vector<string>& line);

    // Receives param index
    template <typename RetType>
    unique_ptr<void> operator[](int index);

private:
    vector<PARAM_TYPES> structure;
    string command_name;
    vector<string> current_line;

    static bool matchNumber(const string& val);
    static bool matchAddress(const string& val);

    void printUsage();
};


#endif //DEBUGGER_PARAMPARSER_H
