//
// Created by John Perry on 2019-04-12.
//

#include <gtest/gtest.h>
#include "Fibonacci.h"
#include <vector>

//fibonacciBasicTests
//  - Tests the basic functionality of the fibonacci_number function
//    for numbers 0, 1, 2, 3 (outputs 0, 1, 1, 2)
TEST(fibonacci_number, fibonacciBasicTests) {
    EXPECT_EQ(0, fibonacci_number(0));
    EXPECT_EQ(1, fibonacci_number(1));
    EXPECT_EQ(1, fibonacci_number(2));
    EXPECT_EQ(2, fibonacci_number(3));
}

//fibonacciBulk40Test
//  - Tests the functionality of fibonacci_number function with the first 40 numbers
//    (the first 40 number outputs are in a vector (first_40_fib_numbers))
//    checked with for loop, looping through the entire size, and comparing using EXPECT_EQ
TEST(fibonacci_number, fibonacciBulk40Test) {
    std::vector<int> first_40_fib_numbers = {
            0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
            89, 144, 233, 377, 610, 987, 1597,
            2584, 4181, 6765, 10946, 17711, 28657,
            46368, 75025, 121393, 196418, 317811,
            514229, 832040, 1346269, 2178309, 3524578,
            5702887, 9227465, 14930352, 24157817, 39088169,
            63245986, 102334155
    };

    for (int i = 0; i < first_40_fib_numbers.size(); i++) {
        EXPECT_EQ(fibonacci_number(i), first_40_fib_numbers[i]);
    }
}

//fibonacciExceptionsTest
//  - Tests the functionality of fibonacci_number function's exceptions
//    1.) invalid_argument exception thrown if fibonacci number is below 0
//    2.) range_error if number is too big (over 46)
//    3.) NO_THROW -> If number is 0 <= x <= 46
TEST(fibonacci_number, fibonacciExceptionsTest) {
    EXPECT_THROW(fibonacci_number(-1), std::invalid_argument);
    EXPECT_THROW(fibonacci_number(-100), std::invalid_argument);
    EXPECT_THROW(fibonacci_number(47), std::range_error);
    EXPECT_THROW(fibonacci_number(100), std::range_error);
    EXPECT_NO_THROW(fibonacci_number(0));
    EXPECT_NO_THROW(fibonacci_number(46));
}
