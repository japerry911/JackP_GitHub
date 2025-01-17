//
// Created by John Perry on 2019-04-12.
//

#include <gtest/gtest.h>
#include "MergeSort.h"

//Briefly used, not used in current setup
#include <iostream>

#include <vector>
#include <string>

//mergeIntTest
//  - Tests whether the Merge works on a vector<int>
//    that is sorted from beginning to mid and mid + 1 to end
TEST(Merge, mergeIntTest) {
    std::vector<int> input_values;
    std::vector<int> expected_sort;

    //2 int test
    input_values = {2, 1};
    expected_sort = {1, 2};
    Merge<int>(input_values, 0, 0, 1);
    EXPECT_EQ(input_values, expected_sort);

    //4 int test
    input_values = {2, 3, 1, 4};
    expected_sort = {1, 2, 3, 4};
    Merge<int>(input_values, 0, 1, 3);
    EXPECT_EQ(input_values, expected_sort);

    //7 int test
    input_values = {1, 4, 10, 2, 8};
    expected_sort = {1, 2, 4, 8, 10};
    Merge<int>(input_values, 0, 2, 4);
    EXPECT_EQ(input_values, expected_sort);
    
    //11 int test
    input_values = {1, 2, 3, 5, 9, 10, 4, 6, 7, 7, 11};
    expected_sort = {1, 2, 3, 4, 5, 6, 7, 7, 9, 10, 11};
    Merge<int>(input_values, 0, 5, 10);
    EXPECT_EQ(input_values, expected_sort);
}

//mergeStringTest
//  - Tests whether the Merge works on a vector<std::string>
//    that is sorted from beginning to mid and mid + 1 to end
TEST(Merge, mergeStringTest) {
    std::vector<std::string> input_values;
    std::vector<std::string> expected_sort;

    //5 string test
    input_values = {
            "canoes", "crazy", "pineapple", "llama", "zebras"
    };
    expected_sort = {
            "canoes", "crazy", "llama", "pineapple", "zebras"
    };
    Merge<std::string>(input_values, 0, 2, 4);
    EXPECT_EQ(input_values, expected_sort);

    //7 string test
    input_values = {
            "canoes", "crazy", "pineapple", "zebras", "allie", "boom", "potato"
    };
    expected_sort = {
            "allie", "boom", "canoes", "crazy", "pineapple", "potato", "zebras"
    };
    Merge<std::string>(input_values, 0, 3, 6);
    EXPECT_EQ(input_values, expected_sort);

    //10 string test
    input_values = {
            "canoes", "crazy", "elephants", "pigs", "zebra",
            "club", "dinosaurs", "dog", "fun", "vectors"
    };
    expected_sort = {
            "canoes", "club", "crazy", "dinosaurs", "dog", "elephants",
            "fun", "pigs", "vectors", "zebra"
    };
    Merge<std::string>(input_values, 0, 4, 9);
    EXPECT_EQ(input_values, expected_sort);
}

//mergeSortIntTest
//  - Tests whether MergeSort works on a vector<int>
//  that is unsorted (randomized in final test)
TEST(MergeSort, mergeSortIntTest) {
    std::vector<int> input_values;
    std::vector<int> expected_sort;

    //2 int test
    input_values = {2, 1};
    expected_sort = {1, 2};
    MergeSort<int>(input_values, 0, 1);
    EXPECT_EQ(input_values, expected_sort);

    //4 int test
    input_values = {3, 2, 4, 1};
    expected_sort = {1, 2, 3, 4};
    MergeSort<int>(input_values, 0, 3);
    EXPECT_EQ(input_values, expected_sort);

    //10 int test
    input_values = {4, 3, 1, 5, 2, 6, 10, 9, 8, 7};
    expected_sort = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MergeSort<int>(input_values, 0, 9);
    EXPECT_EQ(input_values, expected_sort);

    //100 int test
    input_values = {
        92, 85, 42, 1, 29, 36, 62, 70, 14, 66, 86, 88, 91, 73, 61, 24, 52, 10, 83,
        16, 22, 27, 26, 96, 60, 19, 78, 6, 95, 65, 77, 41, 37, 93, 9, 53, 44, 49,
        39, 74, 50, 12, 20, 48, 68, 67, 63, 40, 25, 30, 58, 98, 15, 38, 8, 89, 11,
        72, 64, 45, 21, 18, 87, 35, 54, 71, 7, 97, 33, 84, 47, 31, 81, 69, 59, 17,
        32, 13, 76, 28, 79, 57, 94, 99, 43, 3, 75, 46, 51, 55, 90, 82, 2, 4, 100,
        80, 23, 56, 5, 34
    };
    expected_sort = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
            22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
            58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
            76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
            94, 95, 96, 97, 98, 99, 100
    };
    MergeSort<int>(input_values, 0, 99);
    EXPECT_EQ(input_values, expected_sort);
}

//mergeSortStringTest
//  - Tests whether MergeSort works on a vector<std::string>
//    that is unsorted using random word list (generated by me :D)
TEST(MergeSort, mergeSortStringTest) {
    std::vector<std::string> input_values;
    std::vector<std::string> vector_to_sort;
    std::vector<std::string> expected_sort;

    //50 Word Random Wordlist, created by Jack
    input_values = {
            "zebra", "club", "pizza", "crazy", "fun", "pigs", "elephants", "dinosaurs",
            "vectors", "canoes", "titanic", "vodka", "beer", "rum", "van", "cool",
            "templates", "are", "so", "amazing", "cheese", "sky", "lord", "color", "test",
            "user", "problem", "solving", "assignment", "two", "clear", "emplace", "pop",
            "stack", "square", "sum", "quick", "word", "list", "dictionary", "filter",
            "cranberry", "under", "dog", "curtains", "apartments", "sleep", "homework",
            "pasta", "sharks"
    };

    //3 word test
    for (int i = 0; i < 3; i++) {
        vector_to_sort.push_back(input_values[i]);
    }
    expected_sort = {"club", "pizza", "zebra"};
    MergeSort<std::string>(vector_to_sort, 0, 2);
    EXPECT_EQ(vector_to_sort, expected_sort);
    vector_to_sort.clear();

    //10 word test
    for (int i = 0; i < 10; i++) {
        vector_to_sort.push_back(input_values[i]);
    }
    expected_sort = {"canoes", "club", "crazy", "dinosaurs", "elephants",
                     "fun", "pigs", "pizza", "vectors", "zebra"};
    MergeSort<std::string>(vector_to_sort, 0, 9);
    EXPECT_EQ(vector_to_sort, expected_sort);
    vector_to_sort.clear();

    //30 word test
    for (int i = 0; i < 30; i++) {
        vector_to_sort.push_back(input_values[i]);
    }
    expected_sort = {"amazing", "are", "assignment", "beer", "canoes", "cheese", "club", "color",
                     "cool", "crazy", "dinosaurs", "elephants", "fun", "lord", "pigs", "pizza",
                     "problem", "rum", "sky", "so", "solving", "templates", "test", "titanic",
                     "two", "user", "van", "vectors", "vodka", "zebra"
    };
    MergeSort<std::string>(vector_to_sort, 0, 29);
    EXPECT_EQ(vector_to_sort, expected_sort);
    vector_to_sort.clear();

    //50 word test
    for (int i = 0; i < 50; i++) {
        vector_to_sort.push_back(input_values[i]);
    }
    expected_sort = {"amazing", "apartments", "are", "assignment", "beer", "canoes", "cheese", "clear",
                     "club", "color", "cool", "cranberry", "crazy", "curtains", "dictionary", "dinosaurs",
                     "dog", "elephants", "emplace", "filter", "fun", "homework", "list", "lord", "pasta",
                     "pigs", "pizza", "pop", "problem", "quick", "rum", "sharks", "sky", "sleep", "so", "solving",
                     "square", "stack", "sum", "templates", "test", "titanic", "two", "under", "user", "van",
                     "vectors", "vodka", "word", "zebra"
    };
    MergeSort<std::string>(vector_to_sort, 0, 49);
    EXPECT_EQ(vector_to_sort, expected_sort);
    vector_to_sort.clear();
}

//alreadySortedTest
//  - Tests whether MergeSort works on a vector<int> and vector<std::string>
//    that is already sorted
TEST(MergeSort, alreadySortedTest) {
    //Strings
    std::vector<std::string> input_values_string;

    //5 word test
    input_values_string = {"apple", "beer", "doom", "fish", "mammoth"};
    MergeSort<std::string>(input_values_string, 0, 4);
    EXPECT_EQ(input_values_string, input_values_string);

    //10 word test
    input_values_string = {"apple", "beer", "doom", "fish", "mammoth", "night", "ocean",
                           "pineapple", "sword", "zebra"
    };
    MergeSort<std::string>(input_values_string, 0, 4);
    EXPECT_EQ(input_values_string, input_values_string);

    //Integers
    std::vector<int> input_values_int;

    //5 number test
    input_values_int = {1, 2, 3, 4, 5};
    MergeSort<int>(input_values_int, 0, 4);
    EXPECT_EQ(input_values_int, input_values_int);

    //10 number test
    input_values_int = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MergeSort<int>(input_values_int, 0, 9);
    EXPECT_EQ(input_values_int, input_values_int);
}