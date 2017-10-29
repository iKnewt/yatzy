#include "player.h"
#include "score.h"
#include "print.h"

void Player::playerTurn(){

	score.calculateScores();
	Print::diceOnTable(*this);
	Print::playerHand(*this);

	cout << "[1] Roll\n"
			"[2] Toggle Dice\n"
			"[3] Save hand to Score\n"
			"[4] Print Scoreboard\n"
			"[5] Print explanation for scoreboard\n";
	int playerChoice;
	while(!Tool::tryReadInt(&playerChoice) || playerChoice > 5 || playerChoice < 1)
		cout << "That's not a valid input";

	switch (playerChoice) {
		case 1:
			if(turnsLeft == 0) {
				cout << "You have no turns left, you're going to have to save hand to score.\n";
				Tool::pressToContinue();
			}
			else
				rollDice();
			break;
		case 2:
			toggleDice();
			break;
		case 3:
			saveToScore();
			break;
		case 4:
			Print::scoreBoard(*this);
			break;
		case 5:
			Print::scoreBoardInfo();
			break;
		default:
			break;
	}
}

void Player::saveToScore() {
	score.sortHand(this);
	Print::scoreBoard(*this);
	Print::playerHand(*this);
	cout << "Where would you like to add a score?" << endl;
	int userInput;
	while(!Tool::tryReadInt(&userInput))
		cout << "Ivnalid move\n";

	if(score.value[userInput - 1] != -1)
		cout << "You've already filled that score.\n\n";
	else {
		switch(userInput - 1) {

			case Ones:
			case Twos:
			case Threes:
			case Fours:
			case Fives:
			case Sixes:
				score.value[userInput - 1] = score.checkSameFaces(userInput);
				break;
			case OnePair:
				score.value[userInput - 1] = score.checkForPair();
				break;
			case TwoPairs:
				score.value[userInput - 1] = score.checkForTwoPair();
				break;
			case ThreeOfAKind:
				score.value[userInput - 1] = score.checkForThreeOfAKind();
				break;
			case FourOfAKind:
				score.value[userInput - 1] = score.checkForFourOfAKind();
				break;
			case SmallStraight:
				score.value[userInput - 1] = score.checkForSmallStraight();
				break;
			case LargeStraight:
				score.value[userInput - 1] = score.checkForLargeStraight();
				break;
			case FullHouse:
				score.value[userInput - 1] = score.checkForFullHouse();
				break;
			case Chance:
				score.value[userInput - 1] = score.checkForChance();
				break;
			case Yatzy:
				score.value[userInput - 1] = score.checkForYatzy();
				break;
			case TotalScore:
			case Bonus:
			case UpperTotal:
			case LowerTotal:
			case GrandTotal:
				cout << "You can't change this value\n";
				break;
			default:
				break;
		}
		if (userInput != 0) {
			for(int i = 0; i < 5; i++) {
				dice[i].keep = false;
				dice[i].value = 0;
			}
			turnsLeft += 3;
		}
	}
}

void Player::toggleDice() {
	cout << "Which dice would you like to toggle?" << endl;
	int playerChoice;
	while(!Tool::tryReadInt(&playerChoice) || playerChoice > 5 || playerChoice < 0)
		cout << "That's not a valid input" << endl;

	if(playerChoice == 0)
		return;

	if(dice[playerChoice - 1].keep == false && dice[playerChoice - 1].value != 0)
		dice[playerChoice - 1].keep = true;
	else
		dice[playerChoice - 1].keep = false;
}

void Player::rollDice() {
	turnsLeft -= 1;
	cout << "Rolling dice..\n\n";
	for(int i = 0; i < 5; i++)
		if(dice[i].keep == false)
			dice[i].value = rand() % 6 + 1;
}

void Player::selectPlayerName() {
	cout << "Please give yourself a name: ";
	name = Tool::readLine();
	cout << endl;
}

