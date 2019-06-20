//
// Created by root on 1/16/19.
//

#ifndef ASSIGNMENT_2_WAR_H
#define ASSIGNMENT_2_WAR_H

#include <iostream>
#include <vector>
#include "Card.h"

class War {
public:
    std::vector <Card> getDeckP2();
    void setDeckP2(std::vector <Card> deck);
    std::vector <Card> getDeckMain();
    void setDeckMain(std::vector <Card> deck);
    std::vector <Card> getDeckP1();
    void setDeckP1(std::vector <Card> deck);
    void resetGame();
    bool playHand();
    bool checkGameStatus();
    int countHands();
    int getNumberOfHands();
    int setNumberOfHands(int numOfHands);
    void printDeck(std::vector <Card> deck);

private:
    void addCommonPoolToWinner(std::vector <Card> &commonPool, std::vector <Card> &winner);
    void addToPool(Card player1Card, Card player2Card, std::vector <Card> &commonPool);
    bool warFight(Card player1Card, Card player2Card, std::vector <Card> &commonPool);
    Card drawHand(int playerNumber);
    bool checkNotEnoughCards(int playerNumber);

    std::vector <Card> deckMain;
    std::vector <Card> deckP1;
    std::vector <Card> deckP2;
    int numberOfHands;
    bool isTie;
};


#endif //ASSIGNMENT_2_WAR_H
