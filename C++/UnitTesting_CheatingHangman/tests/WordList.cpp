//
// Created by John Perry on 2019-04-05.
//

#include <gtest/gtest.h>
#include "WordList.h"

#include <string>
#include <vector>

//Test for filter_words_by_length
TEST(filter_words_by_length, filter_words_by_length_test) {
    //Master List of Words
    //3 Letter Words = 5 dog, cat, sky, fun, ice
    //4 Letter Words = 5 bike, moon, cape, ship, home
    //5 Letter Words = 2 pizza, house
    //7 Letter Words = 4 balloon, broncos, testing, monster
    std::vector<std::string> master_list = {"dog", "cat", "bike", "sky", "moon", "pizza", "balloon", "broncos",
                                            "cape", "ship", "testing", "fun", "monster", "house", "home", "ice"};

    //Inputs = Words, Length of Word

    //3 Letter Words
    std::vector<std::string> expected3 = {"dog", "cat", "sky", "fun", "ice"};
    std::vector<std::string> actual3 = filter_words_by_length(master_list, 3);
    EXPECT_EQ(expected3, actual3);

    //4 Letter Words
    std::vector<std::string> expected4 = {"bike", "moon", "cape", "ship", "home"};
    std::vector<std::string> actual4 = filter_words_by_length(master_list, 4);
    EXPECT_EQ(expected4, actual4);

    //5 Letter Words
    std::vector<std::string> expected5 = {"pizza", "house"};
    std::vector<std::string> actual5 = filter_words_by_length(master_list, 5);
    EXPECT_EQ(expected5, actual5);

    //7 Letter Words
    std::vector<std::string> expected7 = {"balloon", "broncos", "testing", "monster"};
    std::vector<std::string> actual7 = filter_words_by_length(master_list, 7);
    EXPECT_EQ(expected7, actual7);
}

//Test for random_sample
TEST(random_sample, random_sample_test) {
    //Creates a finalized game list from the filtered list
    //It'll narrow down the filtered list to to the size inputted with random words with correct length

    //Filtered word list of 10 words (Would come from filter_words_by_length function
    std::vector<std::string> filtered_word_list = {"dog", "cat", "bat", "mat", "bot", "sat", "sit", "tin", "bin", "tip"};

    //Test for Random List of 3 words
    int expected3 = 3;
    int actual3 = random_sample(filtered_word_list, 3).size();
    EXPECT_EQ(expected3, actual3);

    //Test for Random List of 4 words
    int expected4 = 4;
    int actual4 = random_sample(filtered_word_list, 4).size();
    EXPECT_EQ(expected4, actual4);

    //Test for Random List of 5 words
    int expected5 = 5;
    int actual5 = random_sample(filtered_word_list, 5).size();
    EXPECT_EQ(expected5, actual5);
}