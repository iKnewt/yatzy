#ifndef PRINT_H
#define PRINT_H

#include "player.h"

class Print
{
public:

	static void playerHand(Player const& player);
	static void diceOnTable(Player const& player);
	static void scoreBoard(Player const& player);
	static void scoreBoardInfo();

};

#endif // PRINT_H
