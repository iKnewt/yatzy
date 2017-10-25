#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include <vector>


class Player
{
public:

    string name = "Player";
    int turnsLeft = 0;
    int scores[19] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};
    vector<int> diceOnTable;
    vector<int> diceOnHand;

    void selectPlayerName();

    void playerTurn();
    void rollDice();
    void saveToScore();
	void changeHand();
    void keepDice();
    void discardDice();

    void printPlayerHand();
    void printDiceOnTable();
    void printScoreBoard();
    void printScoreBoardInfo();

    void sortHand();
    void calculateScores();
    bool checkForPair();
    int checkSameFaces(int faceValue);
};

#endif // PLAYER_H
