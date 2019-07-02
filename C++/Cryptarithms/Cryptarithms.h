//
// Created by John Perry on 2019-05-07.
//

#ifndef ASSIGNMENT4_TRY1048395_CRYPTARITHMS_H
#define ASSIGNMENT4_TRY1048395_CRYPTARITHMS_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include <ostream>

class Cryptarithms {
public:
    Cryptarithms(const std::vector<std::string> &inputs);
    friend std::ostream &operator<<(std::ostream &os, Cryptarithms &crypt);

    enum class solveState {
        valid, invalid, partial
    };

    solveState status();
    bool addCorrectly();
    void assign(char character, int value);
    void clearMapKeysValues(char character);
    void backtrackSearch();
    void setValueAndPropagate(char position, int value);
    void propagate(char position, int value);
    std::map<char, int> solve();

private:
    std::map<char, std::set<int>> mapOfChars;
    std::map<char, int> solution;
    std::vector<std::string> inputStrings;
    int maxLength = 0;
};

std::ostream &operator<<(std::ostream &os, Cryptarithms &crypt);

#endif //ASSIGNMENT4_TRY1048395_CRYPTARITHMS_H
