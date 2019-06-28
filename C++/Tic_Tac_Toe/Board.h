//
// Created by root on 1/11/19.
//

#ifndef ASSIGNMENT_1_BOARD_H
#define ASSIGNMENT_1_BOARD_H

#include <iostream>
#include<string>
#include<vector>

class Board {
public:
    enum class cellState {
        x, o, e
    };

    bool getMoveValid();
    void resetBoard();
    bool checkStatus();
    void receiveMove(int row, int column, cellState currentPlayer);

    friend std::ostream & operator<<(std::ostream &os, Board &dc);

private:
    std::vector<std::vector<cellState>> outputBoard;
    bool moveValid;
};

std::ostream & operator<<(std::ostream &os, Board &dc);

#endif //ASSIGNMENT_1_BOARD_H
