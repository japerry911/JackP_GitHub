//
// Created by root on 1/11/19.
//

#ifndef ASSIGNMENT_1_MOVE_H
#define ASSIGNMENT_1_MOVE_H

#include <iostream>
#include <vector>

class Move {
public:
    int getRow() const;
    int getColumn() const;

    void setRow(int r);
    void setColumn(int c);

private:
    int row;
    int column;
};


#endif //ASSIGNMENT_1_MOVE_H
