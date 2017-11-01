#include "player.h"
#include "score.h"
#include "print.h"
#include <algorithm>
#include <string>

// returns a bool based on if the player turn should loop again or not
bool Player::playerTurn(Game& game){

	Tool::printSeparator();
	Print::diceOnTable(*this);
	Print::playerHand(*this);

	std::cout << "[1] Toggle dice\n"
				 "[2] Roll\n"
				 "[3] Save hand to Score\n"
				 "[4] Print Scoreboard\n"
				 "[5] More menu options\n";
	if (printLongMenu) {
		std::cout << "[6] Print explanation for scoreboard\n"
					 "[7] Change player name\n"
					 "[8] Change game mode\n"
					 "[9] Remove current player from game\n"
					 "[10] Exit game early\n";
		printLongMenu = false;
	}
	int playerChoice;
	while (!Tool::tryReadInt(&playerChoice) || playerChoice < 1 || playerChoice > 10)
		Tool::errorMessageInvalidInput();

	switch (playerChoice) {
		case 1:
			toggleDice();
			break;
		case 2:
			if (rollsLeft == 0)
				std::cout << "You have no turns left, you're going to have to save hand to score.\n";
			else
				rollDice();
			break;
		case 3:
			if (saveToScore(game)) {
				score.calculateScores();
				Print::scoreBoard(game.players);
				return false;
				break;
			}
		case 4:
			score.calculateScores();
			Print::scoreBoard(game.players);
			break;
		case 5:
			printLongMenu = true;
			break;
		case 6:
			Print::scoreBoardInfo();
			break;
		case 7:
			selectPlayerName();
			break;
		case 8:
			game.selectGameMode();
			break;
		case 9:
			game.removePlayerFromGame(this);
			return false;
			break;
		case 10:
			// sets the gameround to 16 because the game only has 15 rouns and exits after that
			game.round = 16;
			return false;
			break;
		default:
			break;
	}
	return true;
}

// makes the player confirm their save option just in case
// returns a bool to indicate if they want the score or not after seeing it
bool Player::confirmChoice(int turnScore, int userChoice) {
	// this was implemented later so it uses the same string array as the printing of the scoreboard does
	// but it only prints the part of the strings that are relevant to this case
	// which would be from the first space to the first tab
	int start = SCORE_NAME[userChoice].find(' ') + 1;
	int end = SCORE_NAME[userChoice].find('\t') - 3;
	std::cout << "\n" << SCORE_NAME[userChoice].substr(start,end) << "score: " << turnScore
			  << "\n\nConfirm score \n"
				 "[1] Yes\n"
				 "[2] No\n";
	int userInput;
	while (!Tool::tryReadInt(&userInput) || userInput < 0 || userInput > 2)
		Tool::errorMessageInvalidInput();
	switch (userInput) {
		case 1:
			score.value[userChoice] = turnScore;
			return true;
			break;
		default:
			break;
	}
	return false;
}

// either lets the player chose where to save their current hand
// or it does line by line depending on the selected game mode, free or forced
bool Player::saveToScore(Game& game) {
	score.sortHand(this);
	int scoreSelected = 0;
	if (game.gameMode == Free) {
		Print::scoreBoard(game.players);
		Print::playerHand(*this);
		std::cout << "[1-20] add a score\n";
		while (!Tool::tryReadInt(&scoreSelected) || scoreSelected < 0 || scoreSelected > GrandTotal)
			Tool::errorMessageInvalidInput();
	}
	else if (game.gameMode == Forced) {
		if (game.round <= 6)
			scoreSelected = game.round;
		else
			scoreSelected = game.round + 3;
	}
	// used in case the player regrets their choice of where to save their score
	bool exit = false;

	// -1 is used to indicate an inactive/unused score
	if (score.value[scoreSelected - 1] != -1)
		std::cout << "You've already filled that score.\n\n";
	else {
		switch(scoreSelected - 1) {
			case Ones:
			case Twos:
			case Threes:
			case Fours:
			case Fives:
			case Sixes:
				exit = confirmChoice(score.sameFaces(scoreSelected), scoreSelected - 1);
				break;
			case OnePair:
				exit = confirmChoice(score.ofAKind(2,0), scoreSelected - 1);
				break;
			case TwoPairs:
				exit = confirmChoice(score.twoPair(), scoreSelected - 1);
				break;
			case ThreeOfAKind:
				exit = confirmChoice(score.ofAKind(3,0), scoreSelected - 1);
				break;
			case FourOfAKind:
				exit = confirmChoice(score.ofAKind(4,0), scoreSelected - 1);
				break;
			case SmallStraight:
				exit = confirmChoice(score.straight(1), scoreSelected - 1);
				break;
			case LargeStraight:
				exit = confirmChoice(score.straight(2), scoreSelected - 1);
				break;
			case FullHouse:
				exit = confirmChoice(score.fullHouse(), scoreSelected - 1);
				break;
			case Chance:
				exit = confirmChoice(score.chance(), scoreSelected - 1);
				break;
			case Yatzy:
				exit = confirmChoice(score.ofAKind(5,0), scoreSelected - 1);
				break;
			case TotalScore:
			case Bonus:
			case UpperTotal:
			case LowerTotal:
			case GrandTotal:
				std::cout << "You can't change this value\n";
				break;
			default:
				break;
		}
		// resets the unused dice and the amount of rolls after a finished turn
		if (exit) {
			for (int i = 0; i < 5; i++) {
				dice[i].keep = false;
				dice[i].value = 0;
			}
			rollsLeft = 3;
			return true;
		}
	}
	return false;
}

// used to let the player toggle selected dice between keeping or rolling again
// 0 is used to indicate a die before being rolled the first time (to avoid printing them to screen)
void Player::toggleDice() {
	std::cout << "\n[1-5] toggle die\n"
				 "[6] keep all dice\n";
	int userInput;
	while (!Tool::tryReadInt(&userInput) || userInput < 0 || userInput > 6)
		Tool::errorMessageInvalidInput();

	switch (userInput) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (dice[userInput - 1].keep == false && dice[userInput - 1].value != 0)
				dice[userInput - 1].keep = true;
			else
				dice[userInput - 1].keep = false;
			break;
		case 6:
			if (dice[0].value != 0) {
				for (int i = 0; i < 5; i++)
					dice[i].keep = true;
				return;
			}
			break;
		default:
			return;
			break;
	}
}

// gives a random value 1-6 to any dice who are not meant to be kept
void Player::rollDice() {
	rollsLeft -= 1;
	std::cout << "Rolling dice..\n";
	for (int i = 0; i < 5; i++)
		if (dice[i].keep == false)
			dice[i].value = rand() % 6 + 1;
}

// lets the player select a name
// the name is used to keep track of score and who's turn it is
void Player::selectPlayerName() {
	do {
		std::cout << "Player " << playerNumber + 1 << " name: ";
		name = Tool::readLine();
		if (name.size() < 3)
			std::cout << "Your name must be at least three characters long\n";
	} while(name.size() < 3);
	std::cout << std::endl;
}

