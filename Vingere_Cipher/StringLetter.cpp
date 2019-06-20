//
// Created by root on 1/26/19.
//

#include "StringLetter.h"
#include <string>
#include <iostream>

//Operator Overloader that is used in testing
bool operator !=(StringLetter lhs, StringLetter rhs) {
    if (lhs.stringLetter != rhs.stringLetter) {
        return true;
    } else {
        return false;
    }
}

//Operator Overloader used in Encrypting plain text letters
char operator+(StringLetter lhs, StringLetter rhs) {
    if (!std::isalpha(lhs.stringLetter)) {
        return lhs.stringLetter;
    }

    char result;
    char aValue;
    char rhsValue;

    if (std::isupper(lhs.stringLetter)) {
        aValue = 'A';
        rhsValue = std::toupper(rhs.stringLetter);
    } else {
        aValue = 'a';
        rhsValue = std::tolower(rhs.stringLetter);
    }

    result = ((lhs.stringLetter - aValue) + (rhsValue - aValue));

    if (result >= 26) {
        result %= 26;
    }

    result += aValue;

    return result;
}

//Operator Overloader used in decrypting cypher text letters
char operator-(StringLetter lhs, StringLetter rhs) {
    if (!std::isalpha(lhs.stringLetter)) {
        return lhs.stringLetter;
    }

    char result;
    char aValue;
    char rhsValue;

    if (std::isupper(lhs.stringLetter)) {
        aValue = 'A';
        rhsValue = std::toupper(rhs.stringLetter);
    } else {
        aValue = 'a';
        rhsValue = std::tolower(rhs.stringLetter);
    }

    result = ((lhs.stringLetter - aValue) - (rhsValue - aValue));

    if (result < 0) {
        result += 26;
        result %= 26;
    }

    result += aValue;

    return result;
}

//Constructor to form StringLetter stringLetter
StringLetter::StringLetter(char inputtedLetter) {
    stringLetter = inputtedLetter;
}