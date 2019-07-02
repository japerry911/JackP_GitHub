//
// Created by John Perry on 2019-05-07.
//

#include "Cryptarithms.h"
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <map>

//Constructor
Cryptarithms::Cryptarithms(const std::vector<std::string> &inputs) : inputStrings(inputs) {
    for (const auto &inputString : inputStrings) {
        if (maxLength < inputString.size()) {
            maxLength = inputString.size();
        }

        for (const auto character : inputString) {
            if (mapOfChars[tolower(character)].empty()) {
                mapOfChars[tolower(character)] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            }
        }
    }
}

//Operator for ostream <<
std::ostream &operator<<(std::ostream &os, Cryptarithms &crypt) {
    for (const auto &pair : crypt.mapOfChars) {
        os << pair.first << " = {";
        for (const auto outputValue : crypt.mapOfChars[pair.first]) {
            os << outputValue << ",";
        }
        os << "}\n";
    }

    return os;
}

//Status Function for telling whether the puzzle is invalid, partial, or valid
Cryptarithms::solveState Cryptarithms::status() {
    bool unsolved = false;
    for (const auto &pair : mapOfChars) {
        if (mapOfChars[pair.first].empty()) {
            std::cout << pair.first << std::endl;
            return solveState::invalid;
        } else if (mapOfChars[pair.first].size() > 1) {
            unsolved = true;
        }
    }

    if (!addCorrectly()) {
        return solveState::partial;
    }

    if (!unsolved) {
        return solveState::valid;
    } else {
        return solveState::partial;
    }
}

//AddCorrectly Function for telling if the current map value assignments work
bool Cryptarithms::addCorrectly() {
    std::vector<char> toAddLetters;
    int carryOverValue = 0;
    int carryOverValue2 = 0;

    for (int i = inputStrings[inputStrings.size() - 1].size() - 1; i >= 0; --i) {

        int toAddTotal = 0;
        int sumTotal = 0;
        char sumLetter;

        for (const auto &inputString : inputStrings) {
            if (inputString == inputStrings[inputStrings.size() - 1]) {
                sumLetter = tolower(inputString[i]);
                sumTotal = *mapOfChars[sumLetter].begin();
            } else if (inputString.size() < inputStrings[inputStrings.size() - 1].size()) {
                int subtractValue = inputStrings[inputStrings.size() - 1].size() - inputString.size();
                int characterValue = i - subtractValue;

                if (characterValue < 0) {
                    continue;
                }

                toAddLetters.push_back(tolower(inputString[characterValue]));
            } else {
                toAddLetters.push_back(tolower(inputString[i]));
            }
        }

        for (const auto j : toAddLetters) {
            toAddTotal += *mapOfChars[j].begin();
        }

        if (toAddTotal > 9) {
            carryOverValue = toAddTotal / 10;
            toAddTotal = toAddTotal % 10;
        } else {
            carryOverValue = 0;
        }

        toAddLetters.clear();
        toAddTotal += carryOverValue2;

        if (toAddTotal != sumTotal) {
            return false;
        }

        carryOverValue2 = carryOverValue;

        if (carryOverValue > 0 &&  i == 0) {
            return false;
        }
    }

    return true;
}

//Assign Function used for adding in a new value to mapOfChars
void Cryptarithms::assign(char character, int value) {
    mapOfChars[tolower(character)].clear();
    mapOfChars[tolower(character)].insert(value);
}

//ClearMapKeysValues -> Used in tests, since mapOfChars is private
void Cryptarithms::clearMapKeysValues(char character) {
    mapOfChars[tolower(character)].clear();
}


//BacktrackSearch Function used for ultimately solving the Cryptharithm
void Cryptarithms::backtrackSearch() {
    const solveState currentState = status();

    switch (currentState) {
        case solveState::invalid: {
            break;
        }

        case solveState::valid: {
            for (const auto &pair : mapOfChars) {
                solution[pair.first] = *pair.second.begin();
            }
            break;
        }

        case solveState::partial: {
            int counter = 0;
            char position;

            //Looping from the last letter of each word and on
            for (int i = maxLength - 1; i >= 0; --i) {
                for (int s = inputStrings.size() - 1; s >= 0; --s) {
                    if (i - 1 < 0) {
                        continue;
                    }

                    char currentCharacter;

                    if (s == inputStrings.size() - 1) {
                        currentCharacter = tolower(inputStrings[s][i]);
                    } else {
                        //Using this value to make sure I get the right value in smaller sized inputStrings
                        int subtractValue = inputStrings[inputStrings.size() - 1].size() - inputStrings[s].size();
                        int characterValue = i - subtractValue;

                        if (characterValue < 0) {
                            continue;
                        }

                        currentCharacter = tolower(inputStrings[s][characterValue]);
                    }

                    if (mapOfChars[currentCharacter].size() == 1) {
                        ++counter;
                        continue;
                    } else if (mapOfChars[currentCharacter].size() > 1) {
                        position = currentCharacter;
                    } else {
                        throw std::invalid_argument("A char has zero values mapped to it.");
                    }
                }
            }

            std::map<char, std::set<int>> mapCopy = mapOfChars;

            for (const auto value : mapCopy[position]) {
                if (mapCopy[position].size() == 1) {
                    continue;
                }
                setValueAndPropagate(position, value);
                backtrackSearch();
                mapOfChars = mapCopy;
            }
        }
    }
}

//SetValueAndPropagate Function used for propagating the keys and values
void Cryptarithms::setValueAndPropagate(char position, int value) {
    if (mapOfChars[position].count(value) == 0) {
        throw std::logic_error("Attempted to set value in cell when it wasn't an option for that cell.");
    }

    if (mapOfChars[position].size() == 1) {
        return;
    }

    mapOfChars[position].clear();
    mapOfChars[position].insert(value);

    propagate(position, value);
}

//Propagate Function used for the actual propagating of mapOfChars
void Cryptarithms::propagate(char position, int value) {
    for (const auto &pair : mapOfChars) {
        if (pair.first == position) {
            continue;
        }

        if (mapOfChars[pair.first].count(value) == 1) {
            mapOfChars[pair.first].erase(value);

            if (mapOfChars[pair.first].size() == 1) {
                propagate(pair.first, *mapOfChars[pair.first].begin());
            }
        }
    }
}

//Solve Function that just runs backtrackSearch and returns the solution
std::map<char, int> Cryptarithms::solve() {
    backtrackSearch();

    return solution;
}
