#include <iostream>
#include <string>
#include "include/sys_calls.hpp"

int main() {
    std::string filename;
    std::cout << "Enter filename with numbers" << std::endl;
    std::cin >> filename;
    if (filename.empty()) {
        std::cerr << "File shouldn`t be empty" << std::endl;
        return 1;
    }

    sys_call::SysCall oper;
    oper.StartProcesses(filename);
    return 0;
}