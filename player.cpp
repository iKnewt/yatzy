#include "player.h"
#include "score.h"
#include "print.h"
#include <algorithm>

bool Player::playerTurn(Game& game){

	score.calculateScores();
	Print::diceOnTable(*this);
	Print::playerHand(*this);

	std::cout << "[1] Toggle dice\n"
				 "[2] Roll\n"
				 "[3] Save hand to Score\n"
				 "[4] Print Scoreboard\n"
				 "[5] Print explanation for scoreboard\n"
				 "[6] Exit game early\n";
	int playerChoice;
	while (!Tool::tryReadInt(&playerChoice) || playerChoice < 1 || playerChoice > 6)
		Tool::errorMessageInvalidInput();

	switch (playerChoice) {
		case 1:
			toggleDice();
			break;
		case 2:
			if (rollsLeft == 0) {
				std::cout << "You have no turns left, you're going to have to save hand to score.\n";
				Tool::pressToContinue();
			}
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
			Print::scoreBoard(game.players);
			break;
		case 5:
			Print::scoreBoardInfo();
			break;
		case 6:
			game.round = 16;
			return false;
			break;
		default:
			break;
	}
	return true;
}

bool Player::confirmChoice(int turnScore, int userChoice) {
	int start = SCORE_NAME[userChoice].find(' ') + 1;
	int end = SCORE_NAME[userChoice].find('\t') - 3;
	std::cout << SCORE_NAME[userChoice].substr(start,end) << "score: " << turnScore
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

	bool exit;

	if (score.value[scoreSelected - 1] != -1)
		std::cout << "You've already filled that score.\n\n";
	else {
//		switch(scoreSelected - 1) {
//			case Ones:
//			case Twos:
//			case Threes:
//			case Fours:
//			case Fives:
//			case Sixes:
//				exit = confirmChoice(score.ofAKind(scoreSelected), scoreSelected - 1);
//				break;
//			case OnePair:
//				exit = confirmChoice(score.pair(), scoreSelected - 1);
//				break;
//			case TwoPairs:
//				exit = confirmChoice(score.twoPair(), scoreSelected - 1);
//				break;
//			case ThreeOfAKind:
//				exit = confirmChoice(score.threeOfAKind(), scoreSelected - 1);
//				break;
//			case FourOfAKind:
//				exit = confirmChoice(score.fourOfAKind(), scoreSelected - 1);
//				break;
//			case SmallStraight:
//			case LargeStraight:
//				exit = confirmChoice(score.straight(), scoreSelected - 1);
//				break;
//			case FullHouse:
//				exit = confirmChoice(score.fullHouse(), scoreSelected - 1);
//				break;
//			case Chance:
//				exit = confirmChoice(score.chance(), scoreSelected - 1);
//				break;
//			case Yatzy:
//				exit = confirmChoice(score.yatzy(), scoreSelected - 1);
//				break;
//			case TotalScore:
//			case Bonus:
//			case UpperTotal:
//			case LowerTotal:
//			case GrandTotal:
//				std::cout << "You can't change this value\n";
//				break;
//			default:

//				break;
//		}

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
				exit = confirmChoice(score.ofAKind(2), scoreSelected - 1);
				break;
			case TwoPairs:
				exit = confirmChoice(score.twoPair(), scoreSelected - 1);
				break;
			case ThreeOfAKind:
				exit = confirmChoice(score.ofAKind(3), scoreSelected - 1);
				break;
			case FourOfAKind:
				exit = confirmChoice(score.ofAKind(4), scoreSelected - 1);
				break;
			case SmallStraight:
			case LargeStraight:
				exit = confirmChoice(score.straight(), scoreSelected - 1);
				break;
			case FullHouse:
				exit = confirmChoice(score.fullHouse(), scoreSelected - 1);
				break;
			case Chance:
				exit = confirmChoice(score.chance(), scoreSelected - 1);
				break;
			case Yatzy:
				exit = confirmChoice(score.ofAKind(5), scoreSelected - 1);
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



		if (exit) {
			for (int i = 0; i < 5; i++) {
				dice[i].keep = false;
				dice[i].value = 0;
			}
			rollsLeft += 3;
			return true;
		}
	}
	return false;
}

void Player::toggleDice() {
	std::cout << "[1-5] toggle die\n"
				 "[6] keep all dice\n";
	int playerChoice;
	while (!Tool::tryReadInt(&playerChoice) || playerChoice < 0 || playerChoice > 6)
		Tool::errorMessageInvalidInput();

	if (playerChoice == 0)
		return;

	if (playerChoice == 6 && dice[0].value != 0) {
		for (int i = 0; i < 5; i++)
			dice[i].keep = true;
		return;
	}

	if (dice[playerChoice - 1].keep == false && dice[playerChoice - 1].value != 0)
		dice[playerChoice - 1].keep = true;
	else
		dice[playerChoice - 1].keep = false;
}

void Player::rollDice() {
	rollsLeft -= 1;
	std::cout << "Rolling dice..\n\n";
	for (int i = 0; i < 5; i++)
		if (dice[i].keep == false)
			dice[i].value = rand() % 6 + 1;
}

void Player::selectPlayerName() {
	do {
		std::cout << "Player " << playerNumber + 1 << " name: ";
		name = Tool::readLine();
		if (name.size() < 3)
			std::cout << "Your name must be at least three characters long\n";
	} while(name.size() < 3);
	std::cout << std::endl;
}

