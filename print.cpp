#include "print.h"
#include "score.h"
#include <iomanip>
#include <string>

void Print::intro() {
	Tool::printSeparator();
	std::cout << "****** Welcome to Yatzy ******\n\n"

				 "Your goal is to get the highest possible score by rolling and keeping dice.\n"
				 "You can see the explanation for scores and keep track of your scores in the main menu.\n"
				 "The game is played with 5 dice.\n"
				 "Each turn you get three rolls, but the rolls you don't use are saved for later.\n\n"

				 "Use your number keys to navigate the menus,\n"
				 "Tip: use [0] to return to the previous menu at any time.\n\n"

				 "Good luck!\n";
	Tool::printSeparator();
}

void Print::scoreBoardInfo() {
	Tool::printSeparator();
	std::cout << "Score Board explanation\n\n"
				 "Upper Section\n";
	// uses two const-string-arrays (declared in the header) to print the name and explanation for each field on the scoreboard in yatzy
	// the const-arrays are used to easily see and edit the texts as needed while still being able to reuse it other places in the code
	for (int i = 0; i < 20; i++) {
		std::cout << SCORE_NAME[i] << SCORE_INFO[i] << std::endl;

		if (i == UpperTotal)
			std::cout << "\nLower Section\n";
		if (i == LowerTotal)
			std::cout << std::endl;
	}
}

void Print::scoreBoard(std::vector<Player> players) {
	Tool::printSeparator();
	std::cout << "Score Board\t\t";
	// prints the first three characters of each player's name
	for (Player& player : players) {
		std::cout << " | " << player.name[0] << player.name[1] << player.name[2];
	}
	std::cout << " |" << std::endl << std::endl;

	std::cout << "Upper Section\n";
	// uses a const-string-array to print the name for each field on the scoreboard in yatzy (19 in total)
	for (int i = 0; i < 20; i++) {
		std::cout << SCORE_NAME[i];
		for (Player& player : players) {
			// prints the score for each player as long as that value is >=0, because -1 is used to indicate an inactive score
			// the scores may vary in length from 1-3 numbers, so before printing the actual score the field width is set to 3
			// (the maximum possible score will be max 3 long), so it will print nice and even
			if (player.score.value[i] >= 0)
				std::cout << " | " << std::setw(3) << player.score.value[i] << std::setw(0);
			else
				std::cout << " |    ";
		}
		std::cout << " |" << std::endl;

		if (i == UpperTotal)
			std::cout << "\nLower Section\n";
		if (i == LowerTotal)
			std::cout << std::endl;
	}
}

void Print::diceOnTable(Player const& player) {
	// the first row 1-5 is used to indicate wich dice corresponds to what userInput when toggeling dice from table to keep
	std::cout << "Dice number \t | 1 | 2 | 3 | 4 | 5 |\n"
				 "            \t ---------------------\n"
				 "Dice on table \t";
	// prints the die value if any (0 idicates dice before roll) of all dice set to not be kept (eg on the table)
	// leaves a blank space otherwise to keep the positions of the table
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
	// prints the die value if any (0 idicates dice before roll) of all dice set to be kept
	// leaves a blank space otherwise to keep the positions of the table
	for (int i = 0; i < 5; i++)
		if (player.dice[i].keep == true && player.dice[i].value != 0)
			std::cout << " | " << player.dice[i].value;
		else
			std::cout << " |  ";
	std::cout << " | " << std::endl << std::endl;
	// prints the players name and rolls to easily keep track of which player's turn it is and how many rolls they have left
	std::cout << "Player " << player.playerNumber + 1 << " \t " << player.name << std::endl;
	std::cout << "Rolls left \t " << player.rollsLeft << std::endl;
}
