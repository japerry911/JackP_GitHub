#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Move.h"

/*Declaring Make Move function that returns a vector
    - This move asks the player for a row and column for their move and validates that the move's values
    to see if they are integers between 0 and 2 (0, 1, 2)
 */
std::vector<int> makeMove();

//Main function that runs the game, TicTacToe
int main() {
    //Declaring the ticTacBoard as Board Class, resetting it, and then outputting it
    Board ticTacBoard;
    ticTacBoard.resetBoard();
    std::cout << ticTacBoard << std::endl;

    //Declaring Boolean variable to see whether the game is over (true) or not (false)
    bool gameOver = false;

    //Declaring move as Move Class, which will be used to hold the move
    Move move;

    //Declaring variables
    std::vector<int> moveVector;
    int row;
    int column;
    int moveCount = 0;
    std::string outputString;

    //Setting the current player as player o, who plays first
    Board::cellState currentPlayer = Board::cellState::o;

    while (!gameOver) {
        //Creating a string for outputString in order to print who's turn it is
        switch (currentPlayer) {
            case (Board::cellState::o):
                outputString = "Player o's turn.";

                break;

            case (Board::cellState::x):
                outputString = "Player x's turn.";

                break;
        }

        std::cout << outputString << std::endl;

        //Validating/Getting the Move
        do {
            //Calling makeMove function to grab the move into a vector, it is currently validated to be an integer 0, 1, 2
            moveVector = makeMove();

            row = moveVector[0];
            column = moveVector[1];

            move.setRow(row);
            move.setColumn(column);

            //Checking that the move is valid in that no one has claimed the selected spot yet
            ticTacBoard.receiveMove(move.getRow(), move.getColumn(), currentPlayer);
            if (!ticTacBoard.getMoveValid()) {
                std::cout << "That spot has already been played, try again." << std::endl;
            }
        } while (!ticTacBoard.getMoveValid());

        //Printing out the board
        std::cout << ticTacBoard << std::endl;

        //Checking to see whether anyone has won the game
        gameOver = ticTacBoard.checkStatus();

        //Switching the current player to the other player
        switch (currentPlayer) {
            case (Board::cellState::o):
                currentPlayer = Board::cellState::x;

                break;

            case (Board::cellState::x):
                currentPlayer = Board::cellState::o;

                break;
        }

        //Counting moves
        moveCount++;

        //If move total reaches 9, then it is declared a tie
        if (moveCount == 9) {
            outputString = "There are no moves left. The result is a tie.";

            break;
        }
    }

    //If the gameOver = true, and there is a winner then an outputString is set to the winner
    if (gameOver) {
        switch (currentPlayer) {
            case (Board::cellState::o):
                outputString = "Player x wins.";

                break;

            case (Board::cellState::x):
                outputString = "Player o wins.";

                break;
        }
    }

    std::cout << outputString << std::endl;

    return 0;
}

//Function using in finding the move and validating the move to be an integer that is 0, 1, 2
std::vector<int> makeMove() {
    //Declaring variables
    std::vector<int> moveVector;
    bool validationTest = false;
    int row;
    int column;

    //Asking the user for a Row Number
    std::cout << "Enter a row number." << std::endl;
    std::cin >> row;

    //Validating the row number to see if it is a number >= or <= 0 and 2
    do {
        if (row > 2 || row < 0 || (std::cin.fail())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter in a valid row number between 0 and 2." << std::endl;
        } else {
            validationTest = true;
        }
    } while (!validationTest && !(std::cin >> row));

    moveVector.push_back(row);

    validationTest = false;

    //Asking the user for a Column Number
    std::cout << "Enter a column number." << std::endl;
    std::cin >> column;

    //Validating the column number to see if it is a number >= or <= 0 and 2
    do {
        if (column > 2 || column < 0 || (std::cin.fail())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter in a valid column number between 0 and 2." << std::endl;
        } else {
            validationTest = true;
        }
    } while (!validationTest && !(std::cin >> column));

    moveVector.push_back(column);

    //Returning move as a vector
    return moveVector;
}
