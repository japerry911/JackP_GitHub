#include <iostream>
#include "Card.h"
#include "War.h"
#include <vector>
#include <string>

int main() {
    //Declaring Variables that will be used in for simulation for loop
    std::vector <int> numberOfHandsVect;
    int gamesToPlay;
    bool gameOver = false;

    //Asking Player how many games they would like to simulate/validating the input
    bool validationTest = false;
    std::cout << "How many games of War would you like to simulate?" << std::endl;
    std::cin >> gamesToPlay;

    do {
        if (std::cin.fail() || gamesToPlay < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid integer greater than 0." << std::endl;
        } else {
            validationTest = true;
        }
    } while ((!validationTest) && !(std::cin >> gamesToPlay));

    //Declaring War Class variable and resetting game
    War warGame;
    warGame.resetGame();

    //Tests that were used to verify that overloaded operators worked
    /*
    Card testCard1{Card::face::j, Card::suit::diamonds};
    Card testCard2{Card::face::eight, Card::suit::clubs};
    bool testsFinished = false;
    int testNumber = 0;

    while (!testsFinished) {
        if (testNumber > 0) {
            switch (testNumber) {
                case (1):
                    testCard1.setFaceValue(Card::face::q);
                    testCard1.setSuitValue(Card::suit::hearts);
                    testCard2.setFaceValue(Card::face::k);
                    testCard2.setSuitValue(Card::suit::clubs);

                    break;

                case (2):
                    testCard1.setFaceValue(Card::face::two);
                    testCard1.setSuitValue(Card::suit::spades);
                    testCard2.setFaceValue(Card::face::two);
                    testCard2.setSuitValue(Card::suit::hearts);

                    break;

                default:
                    testsFinished = true;

                    break;
            }
        }

        if (testNumber == 0) {
            if (testCard1 < testCard2) {
                std::cout << "Error: Expected JD > 8C, not JD < 8C." << std::endl;
            } else if (testCard1 == testCard2) {
                std::cout << "Error: Expected JD > 8C, not JD == 8C." << std::endl;
            } else {
                std::cout << "Succeeded: JD > 8C." << std::endl;
            }
        } else if (testNumber == 1) {
            if (testCard1 < testCard2) {
                std::cout << "Succeeded: QH < KC." << std::endl;
            } else if (testCard1 == testCard2) {
                std::cout << "Error: Expected QH < KC, not QH == KC." << std::endl;
            } else {
                std::cout << "Error: Expected QH < KC, not QH > KC." << std::endl;
            }
        } else if (testNumber == 2) {
            if (testCard1 < testCard2) {
                std::cout << "Error: Expected 2S == 2H, not 2S < 2H." << std::endl;
            } else if (testCard1 == testCard2) {
                std::cout << "Succeeded: 2S == 2H." << std::endl;
            } else {
                std::cout << "Error: Expected 2S == 2H, not 2S > 2H." << std::endl;
            }
        }

        testNumber++;
    }

    //Used for testing whether the deck was reset correctly/it had the right number of cards in random order
    warGame.printDeck(warGame.getDeckP1());
    std::cout << warGame.getDeckP1().size() << std::endl;
    warGame.printDeck(warGame.getDeckP2());
    std::cout << warGame.getDeckP2().size() << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    */

    //Simulation For Loop
    for (int i = 0; i < gamesToPlay; i++) {
        gameOver = false;
        warGame.resetGame();

        //Simulating One Game of War
        while (!gameOver) {
            gameOver = warGame.playHand();
        }

        // Displays the Number of hands, then Deck 1 + size, then Deck 2 + size for recently ended game
        std::cout << "---------Game #" << (i + 1) << "---------------" << std::endl;
        std::cout << "---------Number of Hands-------" << std::endl;
        std::cout << warGame.getNumberOfHands() << std::endl;
        std::cout << "-------------Deck P1-----------" << std::endl;
        warGame.printDeck(warGame.getDeckP1());
        std::cout << warGame.getDeckP1().size() << std::endl;
        std::cout << "-------------Deck P2-----------" << std::endl;
        warGame.printDeck(warGame.getDeckP2());
        std::cout << warGame.getDeckP2().size() << std::endl;

        //Pushing the number of hands it took to play to a vector that is used at end to calculate average hands
        numberOfHandsVect.push_back(warGame.getNumberOfHands());
    }

    //Declaring Variables used in calculating average hands
    float averageNumberOfHands;
    int grandTotalHands = 0;

    //Calculating total number of hands played in simulation
    for (int i = 0; i < numberOfHandsVect.size(); i++) {
        grandTotalHands += numberOfHandsVect[i];
    }

    //Calculating average of hands played with grand total hands sum
    averageNumberOfHands = grandTotalHands / gamesToPlay;

    //Displaying the average number of hands after simulation
    std::cout << "---------Avg. Hands-----------" << std::endl;
    std::cout << averageNumberOfHands << std::endl;

    return 0;
}
