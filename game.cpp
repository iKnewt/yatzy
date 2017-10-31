#include "game.h"
#include "tool.h"

void Game::loop() { // loops the game
	for (this->round = 1; this->round <= 15; this->round++) { // loops until the game has been played for 15 rounds (the number of different score to fill)
		for (Player& player : players) { // loops for each player in the vector players
			std::cout << "\n\n\n" << player.name << "'s turn\n\n";
			while (player.playerTurn(*this)) {} // runs until playerTurn() returns false;
		}
	}
}

void Game::createPlayers() { // creats the selected amount of players for a game
	std::cout << "\nNumber of players\n";
	int numberOfPlayers = 0;
	while (!Tool::tryReadInt(&numberOfPlayers) || numberOfPlayers < 1 || numberOfPlayers > 9) // prints error message if userInput is not an int between 0 and 10
		Tool::errorMessageInvalidInput();

	for (int i = 0; i < numberOfPlayers; i++) {
		Player player;
		player.playerNumber = i;
		player.selectPlayerName(); // lets the player select a name
		player.score.calculateScores(); // sets the initial scores for each player
		players.push_back(player); // adds the player to the players vector
	}
}

void Game::selectGameMode() { // lets the user decide what gamemode to use
	std::cout << "Play free or forced\n"
				 "[1] Forced\n"
				 "[2] Free\n";
	int userInput;
	while (!Tool::tryReadInt(&userInput) || userInput < 0 || userInput > 2)
		Tool::errorMessageInvalidInput();

	switch (userInput) {
		case 1:
			gameMode = Forced;
			break;
		case 2:
			gameMode = Free;
		default:
			break;
	}
}

int Game::checkWinner() { // checks for the player with the highest score
	int grandTotalScores[players.size()];
	for (Player& player : players) {
		grandTotalScores[player.playerNumber] = player.score.value[GrandTotal];
	}
	std::sort(grandTotalScores, grandTotalScores + players.size());
	for (Player& player : players) {
		if (player.score.value[GrandTotal] == grandTotalScores[players.size() - 1])
			return player.playerNumber;
	}
	return 0;
}
