#include <iostream>
#include <time.h>
#include <random>
#include "player.h"
#include "tool.h"
#include "game.h"
#include "print.h"
#include <string>

int main() {
	// for later generating a random number, should only be done once at the beginning of a program
	srand(time(0));
	do {
		Print::intro();
		Game game;
		game.selectGameMode();
		game.createPlayers();
		game.loop();

		// should replace with something better
		Tool::printSeparator();
		std::cout << "Congratulations, " << game.players[game.checkWinner()].name << " wins!\n\n";
		std::cout << "\nThat's it folks, nothing more to see here...\n";
		Tool::printSeparator();
	} while(true);
	return 0;
}
