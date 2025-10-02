#include <iostream>
#include <string>
#include "include/sys_calls.hpp"

int main() {
    std::string filename;
    std::cout << "Enter filename with numbers" << std::endl;
    std::cin >> filename;

    sys_call::SysCall oper;
    oper.StartProcesses(filename);
    return 0;
}