#include <iostream>
#include "Player.h"
#include "Tool.h"
#include <time.h>
#include <random>

using namespace std;



int main() {
	srand(time(0));
	Player player1;
	//player1.selectPlayerName();
	player1.diceOnTable.resize(5);
	while(true) {
		player1.playerTurn();

//		for(int i = 1; i <= 6; i++)
//			player1.checkSameFaces(i);
//		if(player1.checkForPair())
//			cout << "You have a pair \n"

	}

	return 0;
}
