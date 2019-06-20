//
// Created by root on 1/16/19.
//

#include "War.h"

#include <iostream>
#include <iterator>
#include <random>
#include <algorithm>
#include <vector>
#include "War.h"
#include "Card.h"

//Getters & Setters for Deck1, Deck2, & Main Deck
std::vector <Card> War::getDeckP2() {
    return deckP2;
}

//Used in Testing to verify that the deck dealing had the right number of cards
std::vector <Card> War::getDeckMain() {
    return deckMain;
}

//Not Required
void War::setDeckMain(std::vector <Card> deck) {
    deckMain = deck;
}

//Not Required
void War::setDeckP2(std::vector <Card> deck) {
    deckP2 = deck;
}

//Not Required
void War::setDeckP1(std::vector <Card> deck) {
    deckP1.clear();

    for (int i = 0; i < deck.size(); i++) {
        deckP1.push_back(deck[i]);
    }
}

std::vector <Card> War::getDeckP1() {
    return deckP1;
}

//Resets the game, creates a main deck, shuffles the deck, then deals it out to each player
void War::resetGame() {
    deckMain.clear();
    deckP1.clear();
    deckP2.clear();

    std::vector <Card> newDeck;

    for (int i = 0; i < 4; i++) {
        for (int a = 0; a < 13; a++) {
            newDeck.push_back({Card::face{a}, Card::suit{i}});
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(newDeck.begin(), newDeck.end(), g);

    for (int i = 0; i < 26; i++) {
        deckP1.push_back(newDeck[i]);
    }

    for (int i = 26; i < 52; i++) {
        deckP2.push_back(newDeck[i]);
    }

    numberOfHands = 0;
    isTie = false;
}

//Playing a single hand of War
bool War::playHand() {
    Card handP1;
    Card handP2;

    std::vector <Card> commonPool;
    bool warEnd;

    handP1 = drawHand(1);
    handP2 = drawHand(2);

    //Going into a war fight, fighting each card against eachother
    warEnd = warFight(handP1, handP2, commonPool);

    //Checking status of the game if war did not end in a tie overall
    if (!warEnd) {
        warEnd = checkGameStatus();
    }

    return warEnd;
}

//Checking if one of the players has empty deck
bool War::checkGameStatus() {
    if (deckP1.size() == 0 || deckP2.size() == 0) {
        return true;
    } else {
        return false;
    }
}

//Getter for numberOfHands
int War::getNumberOfHands() {
    return numberOfHands;
}

//Used in setting numberOfHands, everything remains in private for setting this variable; as a result, not required
int War::setNumberOfHands(int numOfHands) {
    numberOfHands = numOfHands;
}

//Printing Deck, used for testing and displaying decks at the end of each game
void War::printDeck(std::vector<Card> deck) {
    std::string output;

    for (int i = 0; i < deck.size(); i++) {
        switch (deck[i].faceValue) {
            case(Card::face::two):
                output += "2, ";
                break;

            case(Card::face::three):
                output += "3, ";
                break;

            case(Card::face::four):
                output += "4, ";
                break;

            case(Card::face::five):
                output += "5, ";
                break;

            case(Card::face::six):
                output += "6, ";
                break;

            case(Card::face::seven):
                output += "7, ";
                break;

            case(Card::face::eight):
                output += "8, ";
                break;

            case(Card::face::nine):
                output += "9, ";
                break;

            case(Card::face::ten):
                output += "10, ";
                break;

            case(Card::face::j):
                output += "J, ";
                break;

            case(Card::face::q):
                output += "Q, ";
                break;

            case(Card::face::k):
                output += "K, ";
                break;

            case(Card::face::a):
                output += "A, ";
                break;
        }
    }

    std::cout << output << std::endl;
}

//Adding commmonpool to winner of hand
void War::addCommonPoolToWinner(std::vector <Card> &commonPool, std::vector <Card> &winner) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(commonPool.begin(), commonPool.end(), g);

    winner.insert(winner.begin(), commonPool.begin(), commonPool.end());
}

//Adding to common pool
void War::addToPool(Card player1Card, Card player2Card, std::vector <Card> &commonPool) {
    commonPool.push_back(player1Card);
    commonPool.push_back(player2Card);
}

//Fighting a hand out of war
bool War::warFight(Card player1Card, Card player2Card, std::vector <Card> &commonPool) {
    if (player1Card < player2Card) {
        numberOfHands++;

        addToPool(player1Card, player2Card, commonPool);

        addCommonPoolToWinner(commonPool, deckP2);
    } else if (player1Card == player2Card) {
        addToPool(player1Card, player2Card, commonPool);

        bool warOver = false;

        //War hand within war (tie breaker essentially)
        while (!warOver) {
            numberOfHands++;

            //Checking if each player has enough cards
            bool notEnoughCards1 = checkNotEnoughCards(1);
            bool notEnoughCards2 = checkNotEnoughCards(2);

            //Checking for tie
            if (notEnoughCards1 && notEnoughCards2) {
                isTie = true;

                return true;
            }

            //Player 1 has not enough cards
            if (notEnoughCards1) {
                addCommonPoolToWinner(commonPool, deckP2);

                return true;
            }

            //Player2 has not enough cards
            if (notEnoughCards2) {
                addCommonPoolToWinner(commonPool, deckP1);

                return true;
            }

            //Drawing extra cards for tie
            Card handP1WarCommon = drawHand(1);
            Card handP2WarCommon = drawHand(2);
            Card handP1WarFight = drawHand(1);
            Card handP2WarFight = drawHand(2);

            addToPool(handP1WarCommon, handP2WarCommon, commonPool);

            if (handP1WarFight < handP2WarFight) {
                addToPool(handP1WarFight, handP2WarFight, commonPool);

                addCommonPoolToWinner(commonPool, deckP2);

                warOver = true;
            } else if (handP1WarFight == handP2WarFight) {
                addToPool(handP1WarFight, handP2WarFight, commonPool);

                continue;
            } else {
                addToPool(handP1WarFight, handP2WarFight, commonPool);

                addCommonPoolToWinner(commonPool, deckP1);

                warOver = true;
            }
        }
    } else {
        numberOfHands++;

        addToPool(player1Card, player2Card, commonPool);

        addCommonPoolToWinner(commonPool, deckP1);
    }

    return false;
}

//Drawing a hand function -> used in starting a war hand
Card War::drawHand(int playerNumber) {
    Card dealtCard;

    switch(playerNumber) {
        case(1):
            dealtCard = deckP1.back();
            deckP1.pop_back();

            break;

        case(2):
            dealtCard = deckP2.back();
            deckP2.pop_back();

            break;
    }

    return dealtCard;
}

//Checks if player has enough cards for war (minimum needed is 2: 1 for war fight, 1 for commonpool deposit)
bool War::checkNotEnoughCards(int playerNumber) {
    bool enoughCards = true;

    switch(playerNumber) {
        case(1):
            if (deckP1.size() >= 2) {
                enoughCards = false;
            } else {
                enoughCards = true;
            }

            break;

        case(2):
            if (deckP2.size() >= 2) {
                enoughCards = false;
            } else {
                enoughCards = true;
            }

            break;
    }

    return enoughCards;
}