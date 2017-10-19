#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include <vector>


class Player
{
public:

    struct Scores {
	int value = 0;
	bool taken = false;
    };


    int numberOfDice = 5;
    int numberOfDiceOnHand = 0;
    int turnsLeft = 0;

    void rollDice();
    void printPlayerHand();
    void selectPlayerName();
    bool checkForPair();
    int checkSameFaces(int faceValue);
    void printScoreBoard();
    void printScoreBoardInfo();
    void printRolledDice();
    void playerTurn();
    void saveToScore();
    void keepDice();
    void discardDice();
    void sortHand();
    void calculateScores();



    int scores[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


    //Die die[5];
    vector<int> diceOnTable;
    string name = "Player";
    vector<int> diceOnHand;


};

#endif // PLAYER_H
