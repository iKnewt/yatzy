#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"

enum GameMode {
	Free,
	Forced,
};

class Game {
public:
	int gameMode;
	int round = 0;
	std::vector<Player> players;

	void loop();
	void createPlayers();
	void selectGameMode();
	int checkWinner();
	void removePlayerFromGame(Player player);
};

#endif // GAME_H
