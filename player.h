#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include "score.h"


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
	Score score;
	Die dice[5];

	void selectPlayerName();
	void playerTurn();
	void rollDice();
	void saveToScore();
	void changeHand();
	void toggleDice();
};

#endif // PLAYER_H
