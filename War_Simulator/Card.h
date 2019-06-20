//
// Created by root on 1/16/19.
//

#ifndef ASSIGNMENT_2_CARD_H
#define ASSIGNMENT_2_CARD_H

#include <iostream>
#include <string>

class Card {
public:
    enum class face {
        two = 0, three, four, five, six, seven, eight, nine, ten, j, q, k, a
    };

    enum class suit {
        hearts = 0, spades, diamonds, clubs
    };

    friend bool operator<(Card lhs, Card rhs);
    friend bool operator==(Card lhs, Card rhs);

    std::string getFaceValue(face fv);
    void setFaceValue(face x);
    void setSuitValue(suit x);

    face faceValue;
    suit suitValue;
};

bool operator<(Card lhs, Card rhs);
bool operator==(Card lhs, Card rhs);

#endif //ASSIGNMENT_2_CARD_H
