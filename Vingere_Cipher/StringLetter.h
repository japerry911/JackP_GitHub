//
// Created by root on 1/26/19.
//

#ifndef ASSIGNMENT_3_TRY4_STRINGLETTER_H
#define ASSIGNMENT_3_TRY4_STRINGLETTER_H

#include <string>

class StringLetter {
public:
    friend char operator+(StringLetter lhs, StringLetter rhs);
    friend char operator-(StringLetter lhs, StringLetter rhs);
    friend bool operator !=(StringLetter lhs, StringLetter rhs);

    StringLetter(char inputtedLetter);

    char stringLetter;
};

char operator+(StringLetter lhs, StringLetter rhs);
char operator-(StringLetter lhs, StringLetter rhs);
bool operator !=(StringLetter lhs, StringLetter rhs);


#endif //ASSIGNMENT_3_TRY4_STRINGLETTER_H
