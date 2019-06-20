//
// Created by root on 1/11/19.
//

#include "Move.h"

//Getters and Setters for row and column protected variables in Move Class

int Move::getRow() const {
    return row;
}

int Move::getColumn() const {
    return column;
}

void Move::setRow(int r) {
    row = r;
}

void Move::setColumn(int c) {
    column = c;
}
