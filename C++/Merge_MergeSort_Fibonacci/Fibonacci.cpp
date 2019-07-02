//
// Created by John Perry on 2019-04-12.
//

#include "Fibonacci.h"
#include <iostream>
#include <cctype>

//fibonacci_number
//  - Calculates the fibonacci number based on the inputted int
int fibonacci_number(int input) {
    //Throws invalid_argument if < 0
    if (input < 0) {
        throw std::invalid_argument("Must input at least 0 or greater.");
    }

    //Throws range_error argument if > 46
    if (input > 46) {
        throw std::range_error("Too large of a fibonacci number to compute.");
    }

    int term1;
    int term2;
    int fib_number;

    for (int i = 0; i <= input; i++) {
        if (i == 0) {
            fib_number = 0;
            continue;
        }

        if (i == 1) {
            fib_number = 1;
            term1 = 0;
            term2 = fib_number;
            continue;
        }

        fib_number = term1 + term2;

        term1 = term2;
        term2 = fib_number;
    }

    return fib_number;
}
