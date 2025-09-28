#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        int num;
        int sum = 0;
        bool is_has_number = false;

        while (ss >> num) {
            sum += num;
            is_has_number = true;
        }

        if (is_has_number) {
            std::cout << sum << std::endl;
        }
    }

    return 0;
}