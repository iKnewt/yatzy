#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include "score.h"
#include "game.h"

class Game;

class Player {
public:
    struct Die {
	int value = 0;
	bool keep = false;
    };

    int playerNumber;
    int rollsLeft = 3;
    Score score;
    std::string name = "Player";
    Die dice[5];

    bool playerTurn(Game& game);
    void selectPlayerName();

private:
    bool confirmChoice(int score, int userChoice);
    void rollDice();
    bool saveToScore(Game& game);
    void changeHand();
    void toggleDice();
};

#endif // PLAYER_H
