#include <iostream>
#include <vector>
#include <string>
#include "Cryptarithms.h"

int main() {
    //Used for fun Functions

    std::vector<std::string> inputs = {"send", "more", "money"};
    Cryptarithms puzzle(inputs);

    std::cout << "Stage 1:" << std::endl;
    std::cout << puzzle << std::endl;

    std::map<char, int> solution = puzzle.solve();

    std::cout << "Stage 2:" << std::endl;
    for (const auto &pair : solution) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    std::vector<std::string> inputs2 = {"saturn", "uranus", "neptune", "pluto", "planets"};
    Cryptarithms puzzle2(inputs2);

    std::cout << "Stage 1:" << std::endl;
    std::cout << puzzle2 << std::endl;

    //Dream
    std::map<char, int> solution3 = puzzle2.solve();

    std::cout << "Stage 2:" << std::endl;
    for (const auto &pair : solution3) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    return 0;
}