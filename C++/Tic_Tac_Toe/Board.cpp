#include "Board.h"

#include<iostream>
#include<string>
#include<vector>

//Getter for moveVaid
bool Board::getMoveValid() {
    return moveValid;
}

//Checking to see if move is not taken yet, if not, it is inputting the move into the board
void Board::receiveMove(int row, int column, cellState currentPlayer) {
    for (int i = 0; i < outputBoard.size(); i++) {
        if (i != row) {
            continue;
        }

        for (int a = 0; a < outputBoard[i].size(); a++) {
            if (a == column) {
                if (outputBoard[i][a] == cellState::e) {
                    outputBoard[i][a] = currentPlayer;

                    moveValid = true;

                    break;

                } else {
                    moveValid = false;

                    break;
                }
            }
        }
    }
}

//Checks to see if anyone has won the game
bool Board::checkStatus() {
    //Declaring variables
    int rowWinx;
    int column0x = 0;
    int column1x = 0;
    int column2x = 0;
    int diagonal0x = 0;
    int diagonal1x = 0;
    int rowWino;
    int column0o = 0;
    int column1o = 0;
    int column2o = 0;
    int diagonal0o = 0;
    int diagonal1o = 0;

    for (int i = 0; i < outputBoard.size(); i++) {
        rowWino = 0;
        rowWinx = 0;

        for (int a = 0; a < outputBoard[i].size(); a++) {
            switch (outputBoard[i][a]) {
                case (Board::cellState::x):
                    switch (a) {
                        case (0):
                            column0x++;

                            if (i == 0) {
                                diagonal0x++;
                            } else if (i == 2) {
                                diagonal1x++;
                            }

                            break;

                        case (1):
                            column1x++;

                            if (i == 1) {
                                diagonal0x++;
                                diagonal1x++;
                            }

                            break;

                        case (2):
                            column2x++;

                            if (i == 0) {
                                diagonal1x++;
                            } else if (i == 2) {
                                diagonal0x++;
                            }

                            break;
                    }

                    rowWinx++;

                    break;

                case (Board::cellState::o):
                    switch (a) {
                        case (0):
                            column0o++;

                            if (i == 0) {
                                diagonal0o++;
                            } else if (i == 2) {
                                diagonal1o++;
                            }

                            break;

                        case (1):
                            column1o++;

                            if (i == 1) {
                                diagonal0o++;
                                diagonal1o++;
                            }

                            break;

                        case (2):
                            column2o++;

                            if (i == 0) {
                                diagonal1o++;
                            } else if (i == 2) {
                                diagonal0o++;
                            }

                            break;
                    }

                    rowWino++;

                    break;

                default:
                    rowWino = 0;
                    rowWinx = 0;

                    break;
            }
        }

        //If there is a 3 returned for either row variable, then there is 3 in a row
        if (rowWinx == 3 || rowWino == 3) {
            return true;
        }

        //If any of these return 3, then there is either 3 in a column or 3 in a diagonal row
        if (column0x == 3 || column1x == 3 || column2x == 3 || diagonal0x == 3 || diagonal1x == 3 ||
                column0o == 3 || column1o == 3 || column2o == 3 || diagonal0o == 3 || diagonal1o== 3) {
            return true;
        }
    }

    return false;
}

//Used to call the Board in std::cout
//Friend of Board Class
std::ostream &operator<<(std::ostream &os, Board &dc) {
    std::string outputValue;

    for (int i = 0; i < dc.outputBoard.size(); i++) {
        for (int a = 0; a < dc.outputBoard[i].size(); a++) {
            switch (dc.outputBoard[i][a]) {
                case (Board::cellState::x):
                    outputValue += "x";

                    break;

                case (Board::cellState::o):
                    outputValue += "o";

                    break;

                default:
                    outputValue += "-";

                    break;
            }
        }
        outputValue += "\n";
    }

    os << outputValue;

    return os;
}

//Resets the board to all emptys
void Board::resetBoard() {
    for (int i = 0; i < 3; i++) {
        std::vector<Board::cellState> row;
        for (int a = 0; a < 3; a++) {
            row.push_back(Board::cellState::e);
        }
        outputBoard.push_back(row);
    }

    moveValid = true;
}
