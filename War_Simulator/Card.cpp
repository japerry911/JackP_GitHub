//
// Created by root on 1/16/19.
//

#include "Card.h"

#include <iostream>
#include <string>

//Used in Testing -> Just returns the face value of the card based on the face enum variable in the card
std::string Card::getFaceValue(Card::face fv) {
    std::string returnValue;

    switch (fv) {
        case (face::a):
            returnValue = "A";

            break;

        case (face::k):
            returnValue = "K";

            break;

        case (face::q):
            returnValue = "Q";

            break;

        case (face::j):
            returnValue = "J";

            break;

        case (face::ten):
            returnValue = "10";

            break;

        case (face::nine):
            returnValue = "9";

            break;

        case (face::eight):
            returnValue = "8";

            break;

        case (face::seven):
            returnValue = "7";

            break;

        case (face::six):
            returnValue = "6";

            break;

        case (face::five):
            returnValue = "5";

            break;

        case (face::four):
            returnValue = "4";

            break;

        case (face::three):
            returnValue = "3";

            break;

        case (face::two):
            returnValue = "2";

            break;
    }

    return returnValue;
}

//Operator Overload for "<" sign. If the face value is < than it's compared against value, it returns true, otherwise false
bool operator<(Card lhs, Card rhs) {
    int value1;
    int value2;

    switch(lhs.faceValue) {
        case(Card::face::two):
            value1 = 2;
            break;

        case(Card::face::three):
            value1 = 3;
            break;

        case(Card::face::four):
            value1 = 4;
            break;

        case(Card::face::five):
            value1 = 5;
            break;

        case(Card::face::six):
            value1 = 6;
            break;

        case(Card::face::seven):
            value1 = 7;
            break;

        case(Card::face::eight):
            value1 = 8;
            break;

        case(Card::face::nine):
            value1 = 9;
            break;

        case(Card::face::ten):
            value1 = 10;
            break;

        case(Card::face::j):
            value1 = 11;
            break;

        case(Card::face::q):
            value1 = 12;
            break;

        case(Card::face::k):
            value1 = 13;
            break;

        case(Card::face::a):
            value1 = 14;
            break;
    }

    switch(rhs.faceValue) {
        case(Card::face::two):
            value2 = 2;
            break;

        case(Card::face::three):
            value2 = 3;
            break;

        case(Card::face::four):
            value2 = 4;
            break;

        case(Card::face::five):
            value2 = 5;
            break;

        case(Card::face::six):
            value2 = 6;
            break;

        case(Card::face::seven):
            value2 = 7;
            break;

        case(Card::face::eight):
            value2 = 8;
            break;

        case(Card::face::nine):
            value2 = 9;
            break;

        case(Card::face::ten):
            value2 = 10;
            break;

        case(Card::face::j):
            value2 = 11;
            break;

        case(Card::face::q):
            value2 = 12;
            break;

        case(Card::face::k):
            value2 = 13;
            break;

        case(Card::face::a):
            value2 = 14;
            break;
    }

    if (value1 < value2) {
        return true;
    } else {
        return false;
    }
}

//Operator Overload for "==" sign. If the face value is == than it's compared against value, it returns true, otherwise false
bool operator==(Card lhs, Card rhs) {
    int value1;
    int value2;

    switch(lhs.faceValue) {
        case(Card::face::two):
            value1 = 2;
            break;

        case(Card::face::three):
            value1 = 3;
            break;

        case(Card::face::four):
            value1 = 4;
            break;

        case(Card::face::five):
            value1 = 5;
            break;

        case(Card::face::six):
            value1 = 6;
            break;

        case(Card::face::seven):
            value1 = 7;
            break;

        case(Card::face::eight):
            value1 = 8;
            break;

        case(Card::face::nine):
            value1 = 9;
            break;

        case(Card::face::ten):
            value1 = 10;
            break;

        case(Card::face::j):
            value1 = 11;
            break;

        case(Card::face::q):
            value1 = 12;
            break;

        case(Card::face::k):
            value1 = 13;
            break;

        case(Card::face::a):
            value1 = 14;
            break;
    }

    switch(rhs.faceValue) {
        case(Card::face::two):
            value2 = 2;
            break;

        case(Card::face::three):
            value2 = 3;
            break;

        case(Card::face::four):
            value2 = 4;
            break;

        case(Card::face::five):
            value2 = 5;
            break;

        case(Card::face::six):
            value2 = 6;
            break;

        case(Card::face::seven):
            value2 = 7;
            break;

        case(Card::face::eight):
            value2 = 8;
            break;

        case(Card::face::nine):
            value2 = 9;
            break;

        case(Card::face::ten):
            value2 = 10;
            break;

        case(Card::face::j):
            value2 = 11;
            break;

        case(Card::face::q):
            value2 = 12;
            break;

        case(Card::face::k):
            value2 = 13;
            break;

        case(Card::face::a):
            value2 = 14;
            break;
    }

    if (value1 == value2) {
        return true;
    } else {
        return false;
    }
}

//Setters used in testing for the face and suit enum variables of the Card class
void Card::setFaceValue(face x) {
    faceValue = x;
}

void Card::setSuitValue(suit x) {
    suitValue = x;
}