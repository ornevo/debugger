//
// Created by ororor012 on 09/11/18.
//

#ifndef DEBUGGER_IO_H
#define DEBUGGER_IO_H

#include <string>
#include <vector>

using namespace std;


#define SAVED_HISTORY_PATH "/etc/my-debugger.history"
#define PROMPT "O>~~> "


class IO {
public:
    static void init();
    static void destruct();
    static vector<string> nextCommand();

private:
    static bool did_init;
};


#endif //DEBUGGER_IO_H
