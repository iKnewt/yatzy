#include "print.h"
#include "score.h"
#include <iomanip>

void Print::intro() {
	std::cout << "\n"
			"****** Welcome to Yatzy ******\n\n"

			"Your goal is to get the highest possible score by rolling and keeping dice.\n"
			"You can see the explanation for scores and keep track of your scores in the main menu.\n"
			"The game is played with 5 dice.\n"
			"Each turn you get three rolls, but the rolls you don't use are saved for later.\n\n"

			"Use your number keys to navigate the menus,\n"
			"use [0] to return to the previous menu at any time.\n\n"

			"Good luck!\n\n\n";
}

void Print::scoreBoardInfo() {
	std::cout << "\n\n"
				 "Score Board explanation\n\n"
							"Upper Section\n";
	for (int i = 0; i < 20; i++) {
		std::cout << SCORE_NAME[i] << SCORE_INFO[i] << std::endl;
		if (i == UpperTotal)
			std::cout << "\nLower Section\n";
		if (i == LowerTotal)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Print::scoreBoard(std::vector<Player> players) {

	int numberOfPlayers = players.size();
	std::cout << std::endl << std::endl << "Score Board\t\t";

	for (int i = 0; i < numberOfPlayers; i++) {
		std::cout << " | " << players[i].name[0] << players[i].name[1] << players[i].name[2];
	}
	std::cout << " |" << std::endl << std::endl;

	std::cout << "Upper Section\n";

	for (int i = 0; i < 20; i++) {
		std::cout << SCORE_NAME[i];
		for (int j = 0; j < numberOfPlayers; j++) {
			if (players[j].score.value[i] >= 0)
				std::cout << " | " << std::setw(3) << players[j].score.value[i] << std::setw(0);
			else
				std::cout << " |    ";
		}
		std::cout << " |" << std::endl;

		if (i == UpperTotal)
			std::cout << "\nLower Section\n";
		if (i == LowerTotal)
			std::cout << std::endl;
	}
	std::cout << "\n---------------------------------------------------------\n";
}

void Print::diceOnTable(Player const& player) {
	std::cout << "Dice number \t | 1 | 2 | 3 | 4 | 5 |\n"
			"            \t ---------------------\n"
			"Dice on table \t";
	for (int i = 0; i < 5; i++) {
		if (player.dice[i].keep == false && player.dice[i].value != 0)
			std::cout << " | " << player.dice[i].value;
		else
			std::cout << " |  ";
	}
	std::cout << " | " << std::endl;
}

void Print::playerHand(Player const& player) {
	std::cout << "Dice to keep\t";
	for (int i = 0; i < 5; i++)
		if (player.dice[i].keep == true && player.dice[i].value != 0)
			std::cout << " | " << player.dice[i].value;
		else
			std::cout << " |  ";
	std::cout << " | " << std::endl << std::endl;
	std::cout << "Player:\t\t" << player.name << std::endl;
	std::cout << "Turns left:\t" << player.rollsLeft << std::endl;
	std::cout << "Score:\t\t" << player.score.value[GrandTotal] << std::endl << std::endl;
}
