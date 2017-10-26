#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include <vector>


class Player
{
public:

	struct Die
	{
		int value = 0;
		bool keep = false;
	};

	string name = "Player";
	int turnsLeft = 3;
	int score[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	Die dice[5];
	vector<int> diceForScore = {0,0,0,0,0};

	void selectPlayerName();

	void playerTurn();
	void rollDice();
	void saveToScore();
	void changeHand();
	void toggleDice();

	void sortHand();
	void calculateScores();
	int checkForPair();
	int checkForTwoPair();
	int checkSameFaces(int faceValue);
	int checkForYatzy();
	int checkForChance();
	int checkForThreeOfAKind();
	int checkForFourOfAKind();
	int checkForSmallStraight();
	int checkForLargeStraight();
	int checkForFullHouse();
};

#endif // PLAYER_H
