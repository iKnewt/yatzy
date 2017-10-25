#include <iostream>
#include "Player.h"
#include "Tool.h"
#include <time.h>
#include <random>

using namespace std;



int main() {
	srand(time(0)); // for later generating a random number, should only be done once at the beginning of a program
	Player* player1 = new Player;

//	Player player1;
	//player1.selectPlayerName();
	player1->diceOnTable.resize(5);
	while(true) {
		player1->playerTurn();
	}

	delete player1;
	player1 = nullptr;
	return 0;
}
