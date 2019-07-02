//
// Created by John Perry on 2019-04-05.
//

#include <gtest/gtest.h>

#include "Hangman.h"
#include <string>
#include <vector>
#include <map>

//Note: apply_guess is tested in the following tests by being used:
//  - status_test
//  - is_valid_guess_test
//  - get_last_partition_test
//  - get_current_hint_test

//Test for status
TEST(status, status_test) {
    //Master Word List used in testing
    std::vector<std::string> master_list = {"sky"};
    Hangman game1(master_list, 1, false);

    //not_over test
    EXPECT_EQ(game1.status(), Hangman::game_status::not_over);

    //Loss test
    game1.apply_guess("t");
    EXPECT_EQ(game1.status(), Hangman::game_status::loss);

    //Redeclaring Game for win test
    Hangman game2(master_list, 1, false);

    //Win test
    game2.apply_guess("s");
    game2.apply_guess("k");
    game2.apply_guess("y");
    EXPECT_EQ(game2.status(), Hangman::game_status::win);
}

//Test for is_valid_guess
TEST(is_valid_guess, is_valid_guess_test) {
    //Master Word List used in testing
    std::vector<std::string> master_list = {"sky"};
    Hangman game(master_list, 5, false);
    std::string guess;

    //incorrect length test
    guess = "aa";
    EXPECT_EQ(game.is_valid_guess(guess), Hangman::guess_validity::incorrect_length);

    //non_letter test
    guess = "@";
    EXPECT_EQ(game.is_valid_guess(guess), Hangman::guess_validity::non_letter);

    //repeat guess test
    guess = "a";
    game.apply_guess(guess);
    EXPECT_EQ(game.is_valid_guess(guess), Hangman::guess_validity::repeat_guess);

    //valid guess test
    guess = "d";
    EXPECT_EQ(game.is_valid_guess(guess), Hangman::guess_validity::valid);
}

//Test for get_last_partition
TEST(get_last_partition, get_last_partition_test) {
    std::map<std::string, std::vector<std::string>> expected;
    std::vector<std::string> word_list = {"sky", "ski", "see"};
    Hangman game(word_list, 5, false);

    expected["sk_"] = {"sky", "ski"};
    expected["s__"] = {"see"};

    game.apply_guess("s");
    game.apply_guess("k");

    EXPECT_EQ(game.get_last_partition(), expected);
}

//Test for get_current_hint
TEST(get_current_hint, get_current_hint_test) {
    std::vector<std::string> word_list = {"sky"};
    Hangman game(word_list, 5, false);

    std::string expected = "s__";

    game.apply_guess("s");

    EXPECT_EQ(game.get_current_hint(), expected);
}

//Test for final word
TEST(final_word, final_word_test) {
    std::vector<std::string> word_list = {"sky"};
    Hangman game(word_list, 5, false);

    std::string expected = "sky";

    EXPECT_EQ(game.final_word(), expected);
}