#include <iostream>
#include <time.h>
#include <random>
#include "player.h"
#include "tool.h"
#include "game.h"
#include "print.h"

int main() {
	srand(time(0)); // for later generating a random number, should only be done once at the beginning of a program

	Print::intro();
	Game game;
	game.selectGameMode();
	game.createPlayers();
	game.loop();

	std::cout << "\n\ncongratulations, " << game.players[game.checkWinner()].name << " wins!\n\n"; // will replace with something better
	return 0;
}
