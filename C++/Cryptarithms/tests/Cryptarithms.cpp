//
// Created by John Perry on 2019-05-07.
//

#include <gtest/gtest.h>
#include "Cryptarithms.h"
#include <vector>
#include <string>
#include <sstream>

//Constructor Test
TEST(Cryptarithms, Constructor_Test) {
    std::stringstream outStream;
    std::string expected;
    std::vector<std::string> inputs;

    inputs = {"send", "more", "money"};
    Cryptarithms puzzle1(inputs);
    outStream << puzzle1;
    expected =
            "d = {0,1,2,3,4,5,6,7,8,9,}\n"
            "e = {0,1,2,3,4,5,6,7,8,9,}\n"
            "m = {0,1,2,3,4,5,6,7,8,9,}\n"
            "n = {0,1,2,3,4,5,6,7,8,9,}\n"
            "o = {0,1,2,3,4,5,6,7,8,9,}\n"
            "r = {0,1,2,3,4,5,6,7,8,9,}\n"
            "s = {0,1,2,3,4,5,6,7,8,9,}\n"
            "y = {0,1,2,3,4,5,6,7,8,9,}\n";
    EXPECT_EQ(outStream.str(), expected);
}

//Status / AddCorrectly Test
TEST(status, StatusAddCorrectly_Test) {
    Cryptarithms::solveState expected;
    std::vector<std::string> inputs = {"send", "more", "money"};

    //Valid Test
    expected = Cryptarithms::solveState::valid;
    Cryptarithms puzzle1(inputs);
    puzzle1.assign('o', 0);
    puzzle1.assign('m', 1);
    puzzle1.assign('y', 2);
    puzzle1.assign('e', 5);
    puzzle1.assign('n', 6);
    puzzle1.assign('d', 7);
    puzzle1.assign('r', 8);
    puzzle1.assign('s', 9);
    EXPECT_EQ(puzzle1.status(), expected);

    //Partial Test
    expected = Cryptarithms::solveState::partial;
    Cryptarithms puzzle2(inputs);
    EXPECT_EQ(puzzle2.status(), expected);

    //Invalid Test
    expected = Cryptarithms::solveState::invalid;
    puzzle2.clearMapKeysValues('s');
    EXPECT_EQ(puzzle2.status(), expected);
}

//Solve Test
TEST(solve, Solve_Test) {
    std::vector<std::string> inputs;
    std::map<char, int> expected;

    //Takes around 1.25 minutes to solve
    inputs = {"SENd", "more", "money"};
    expected['d'] = 7;
    expected['e'] = 5;
    expected['m'] = 1;
    expected['n'] = 6;
    expected['o'] = 0;
    expected['r'] = 8;
    expected['s'] = 9;
    expected['y'] = 2;
    Cryptarithms puzzle1(inputs);
    EXPECT_EQ(puzzle1.solve(), expected);

    inputs.clear();
    expected.clear();

    //Takes about 4.25 minutes to solve
    inputs = {"SATURN", "uranus", "NEPTUNE", "pluto", "PLAnets"};
    expected['a'] = 2;
    expected['e'] = 9;
    expected['l'] = 6;
    expected['n'] = 3;
    expected['o'] = 8;
    expected['p'] = 4;
    expected['r'] = 0;
    expected['s'] = 1;
    expected['t'] = 7;
    expected['u'] = 5;
    Cryptarithms puzzle3(inputs);
    EXPECT_EQ(puzzle3.solve(), expected);
}