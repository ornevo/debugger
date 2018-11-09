#include <iostream>
#include <sys/ptrace.h>
#include <zconf.h>
#include "Debugger.h"
#include "IO.h"

using namespace std;


int main(int argc, char ** argv) {
    if(argc < 2)
        cout << "No executable supplied." << endl;
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <path to exec>" << endl;
        return 1;
    }

    const char * prog_name = argv[1];

    auto pid = fork();
    if(pid == 0)  // child process
    {
        // Request, pid, addr, data
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(prog_name, prog_name, nullptr);
    }
    else // Debugger process
    {
        IO::init();

        Debugger::get(prog_name, pid);
        Debugger::get().run();

        Debugger::get().killChild();
        IO::destruct();
    }
}