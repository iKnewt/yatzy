#include "Player.h"
#include "Score.h"
#include "Print.h"


void Player::playerTurn(){


    calculateScores();
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
    sortHand();
    Print::scoreBoard(*this);
    Print::playerHand(*this);
    cout << "Where would you like to add a score?" << endl;
    int userInput;
    while(!Tool::tryReadInt(&userInput))
	cout << "Ivnalid move\n";

    if(score[userInput-1] != -1)
	cout << "You've already filled that score.\n\n";
    else {
	switch(userInput - 1) {

	    case Ones:
	    case Twos:
	    case Threes:
	    case Fours:
	    case Fives:
	    case Sixes:
		score[userInput - 1] = checkSameFaces(userInput);
		break;

	    case OnePair:

		break;
	    case TwoPairs:

		break;
	    case ThreeOfAKind:

		break;
	    case FourOfAKind:

		break;
	    case SmallStraight:

		break;
	    case LargeStraight:

		break;
	    case FullHouse:

		break;
	    case Chance:

		break;
	    case Yatzy:

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

void Player::calculateScores() {
    score[TotalScore] = 0;
    score[UpperTotal] = 0;
    score[LowerTotal] = 0;
    score[GrandTotal] = 0;

    for(int i = Ones; i <= Sixes; i++)
	if(score[i] >= 0)
	    score[TotalScore] += score[i];
    if(score[TotalScore] >= 63) {
	score[Bonus] = 50;
	score[UpperTotal] += score[Bonus];
    }
    score[UpperTotal] += score[TotalScore];

    for(int i = OnePair; i <= Yatzy; i++)
	if(score[i] >= 0)
	    score[LowerTotal] += score[i];
    score[GrandTotal] = score[UpperTotal] + score[LowerTotal];
}

void Player::sortHand() {
    diceForScore.clear();
    for(int i = 0; i < 5; i++)
	if(dice[i].keep == true)
	    diceForScore.push_back(dice[i].value);
    sort(diceForScore.begin(), diceForScore.end()); // sorts the dice on hand after value to easily compare the dice
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

bool Player::checkForPair() {
    int handSize = diceForScore.size();
    for(int i = 0; i < handSize; i++)
	if(diceOnHand[i] == diceOnHand[i+1])
	    return true;
    return false;
}

int Player::checkSameFaces(int faceValue) {
    int handSize = diceForScore.size();
    int sameFaces = 0;
    for(int i = 0; i < handSize; i++)
	if(diceForScore[i] == faceValue)
	    sameFaces++;
    return faceValue * sameFaces;
}
