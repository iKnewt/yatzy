#include "game.h"
#include "tool.h"
#include <string>

void Game::loop() {
	for (this->round = 1; this->round <= 15; this->round++) { // loops until the game has been played for 15 rounds (the number of different score to fill)
		for (Player& player : players) { // loops for each player in the vector players
			Tool::printSeparator();
			std::cout << player.name << "'s turn\n";
			while (player.playerTurn(*this)) {} // runs until playerTurn() returns false;
		}
	}
}

void Game::createPlayers() {
	std::cout << "\n[1-9] Number of players\n";
	int numberOfPlayers = 0;
	while (!Tool::tryReadInt(&numberOfPlayers) || numberOfPlayers < 1 || numberOfPlayers > 9) // prints error message if userInput is not an int between 0 and 10
		Tool::errorMessageInvalidInput();
	std::cout << std::endl;

	for (int i = 0; i < numberOfPlayers; i++) {
		Player player;
		player.playerNumber = i;
		player.selectPlayerName(); // lets the player select a name
		player.score.calculateScores(); // sets the initial scores for each player
		players.push_back(player); // adds the player to the players vector
	}
}

void Game::selectGameMode() {
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

int Game::checkWinner() {
	std::vector<int> grandTotalScores;
	for (Player& player : players) {
		grandTotalScores.push_back(player.score.value[GrandTotal]);
	}
	sort(grandTotalScores.begin(), grandTotalScores.end());
	for (Player& player : players) {
		if (player.score.value[GrandTotal] == grandTotalScores[players.size() - 1])
			return player.playerNumber;
	}
	return 0;
}

// doesn't function quite as intended yet
void Game::removePlayerFromGame(Player player) {
	std::cout << "Removing " << player.name << " from game\n";
	std::cout << "Confirm decision\n"
				 "[1] Yes\n"
				 "[2] No\n";
	int userInput = 0;
	while (!Tool::tryReadInt(&userInput) || userInput < 0 || userInput > 2)
		Tool::errorMessageInvalidInput();

	switch (userInput) {
		case 1:
			players.erase(players.begin() + player.playerNumber);
			break;
		default:
			break;
	}
}
