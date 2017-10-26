#include <iostream>
#include <time.h>
#include <random>
#include "Player.h"
#include "Tool.h"

using namespace std;

int main() {
	srand(time(0)); // for later generating a random number, should only be done once at the beginning of a program

	cout << "Yatzy\n\n"
			"Welcome to a simple one-player game of yatzy\n"
			"Your goal is to get the highest possible score by rolling and keeping dice.\n"
			"You can see the explanation for scores and keep track of your scores in the main menu.\n"
			"The game is played with 5 dice.\n"
			"Each turn you get three rolls, but the rolls you don't use are saved for later.\n\n"
			"Good luck!\n\n";
	Tool::pressToContinue();
	cout << "\n\n\n\n";

	Player* player1 = new Player;
	//player1.selectPlayerName();
	while(true) {
		player1->playerTurn();
	}

	delete player1;
	player1 = nullptr;
	return 0;
}
