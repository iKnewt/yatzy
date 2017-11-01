#include "game.h"
#include "tool.h"
#include <string>

// loops until the game has been played for 15 rounds (the number of different score to fill)
void Game::loop() {
	for (this->round = 1; this->round <= 15; this->round++) {
		// fixes up the player-vector in case a player has been removed from game
		// still a WIP and not fully implemented hence the awkward positioning
		reArrangePlayers();
		// loops for each player in the vector players
		for (Player& player : players) {
			Tool::printSeparator();
			std::cout << player.name << "'s turn\n";
			// runs until playerTurn() returns false;
			while (player.playerTurn(*this)) {}
		}
	}
}

// creates and fills the vector of players in the game
void Game::createPlayers() {
	std::cout << "\n[1-9] Number of players\n";
	int numberOfPlayers = 0;
	// prints error message if userInput is not an int between 0 and 10
	while (!Tool::tryReadInt(&numberOfPlayers) || numberOfPlayers < 1 || numberOfPlayers > 9)
		Tool::errorMessageInvalidInput();
	std::cout << std::endl;

	for (int i = 0; i < numberOfPlayers; i++) {
		Player player;
		player.playerNumber = i;
		player.selectPlayerName();
		// used to set initial scores
		player.score.calculateScores();
		players.push_back(player);
	}
}

// lets the user chose to play free or forced
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

// compares the playes final scores and returns the vector-position of the player with the highest score
// a little flawed as it does not consider draws
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
// it can only delete this and that many
// more of a WIP-bonus in case someone drops out of the game but the rest still want to keep playing
void Game::removePlayerFromGame(Player* player) {
	std::cout << "\n" << player->name << " will be removed from the game at the end of the round\n";
	std::cout << "Confirm decision\n"
				 "[1] Yes\n"
				 "[2] No\n";
	int userInput = 0;
	while (!Tool::tryReadInt(&userInput) || userInput < 0 || userInput > 2)
		Tool::errorMessageInvalidInput();

	switch (userInput) {
		case 1:
			player->activePlayer = false;
			break;
		default:
			break;
	}
}

// same as the above method
void Game::reArrangePlayers() {
	for (Player& player : players) {
		if (!player.activePlayer)
			players.erase(players.begin() + player.playerNumber);
		break;
	}
	for (size_t j = 0; j < players.size(); j++)
		players[j].playerNumber = j;
}
