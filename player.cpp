#include "Player.h"

enum Scores {
    Ones,
    Twos,
    Threes,
    Fours,
    Fives,
    Sixes,
    TotalScore,
    Bonus,
    UpperTotal,

    OnePair,
    TwoPairs,
    ThreeOfAKind,
    FourOfAKind,
    SmallStraight,
    LargeStraight,
    FullHouse,
    Chance,
    Yatzy,
    LowerTotal,

    GrandTotal,
};

static const string SCORE_NAME[] = {
    "[1] Ones \t\t",		//0
    "[2] Twos \t\t",		//1
    "[3] Threes \t\t",		//2
    "[4] Fours \t\t",		//3
    "[5] Fives \t\t",		//4
    "[6] Sixes \t\t",		//5
    "[7] Total Score \t",	//6
    "[8] Bonus \t\t",		//7
    "[9] Upper Total \t",	//8

    "[10] One Pair \t\t",	//9
    "[11] Two Pairs \t\t",	//10
    "[12] 3 of a kind \t",	//11
    "[13] 4 of a kind \t",	//12
    "[14] Small Straight \t",	//13
    "[15] Large straight \t",	//14
    "[16] Full House \t",	//15
    "[17] Chance \t\t",		//16
    "[18] YATZY \t\t",		//17
    "[19] Lower Total\t",	//18

    "[20] Grand Total \t",	//19
};

static const string SCORE_INFO[] = {
    "The sum of all dice showing the number 1",
    "The sum of all dice showing the number 2",
    "The sum of all dice showing the number 3",
    "The sum of all dice showing the number 4",
    "The sum of all dice showing the number 5",
    "The sum of all dice showing the number 6",
    "",
    "If total score is 63 or over you get 50 bonus points",
    "",

    "Two dice showing the same number. Score: Sum of those two dice",
    "Two different pairs of dice. Score: Sum of dice in those two pairs",
    "Three dice showing the same number. Score: Sum of those three dice",
    "Four dice with the same number. Score: Sum of those four dice.",
    "The combination 1-2-3-4-5. Score: 15 points (sum of all the dice)",
    "The combination 2-3-4-5-6. Score: 20 points (sum of all the dice)",
    "Any set of three combined with a different pair. Score: Sum of all the dice.",
    "Any combination of dice. Score: Sum of all the dice.",
    "All five dice with the same number. Score: 50 points.",
    "",
    "",
};

void Player::playerTurn(){


    calculateScores();
    printDiceOnTable();
    printPlayerHand();

    cout << "[1] Roll\n"
            "[2] Change hand\n"
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
	    changeHand();
	    break;
	case 3:
	    saveToScore();
	    break;
	case 4:
	    printScoreBoard();
	    break;
	case 5:
	    printScoreBoardInfo();
	    break;
	default:
	    break;
    }
}

void Player::changeHand() {
    bool cont = true;
    while(cont) {
	printDiceOnTable();
	printPlayerHand();
	cout << "What would you like to do?\n"
	        "[1] Keep one dice\n"
	        "[2] Discard one dice\n"
	        "[3] Continue game\n";
	int playerChoice;
	while(!Tool::tryReadInt(&playerChoice))
	    cout << "Invalid input\n";

	switch (playerChoice) {
	    case 1:
		keepDice();
		break;
	    case 2:
		discardDice();
		break;
	    case 3:
		cont = false;
		break;
	    default:
		break;
	}
    }
}

void Player::saveToScore() {
    sortHand();
    printScoreBoard();
    printPlayerHand();
    cout << "Where would you like to add a score?" << endl;
    int userInput;
    while(!Tool::tryReadInt(&userInput))
	cout << "Ivnalid move\n";

    if(score[userInput-1] != -1)
	cout << "You've already filled that score.\n\n";
    else {
	switch(userInput-1) {
	    case Ones:
		score[Ones] = checkSameFaces(1);
		break;
	    case Twos:
		score[Twos] = checkSameFaces(2);
		break;
	    case Threes:
		score[Threes] = checkSameFaces(3);
		break;
	    case Fours:
		score[Fours] = checkSameFaces(4);
		break;
	    case Fives:
		score[Fives] = checkSameFaces(5);
		break;
	    case Sixes:
		score[Sixes] = checkSameFaces(6);
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
	    diceOnHand.clear();
	    diceOnTable.clear();
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
    sort(diceOnHand.begin(), diceOnHand.end()); // sorts the dice on hand after value to easily compare the dice
}

void Player::printScoreBoardInfo() {
    cout << endl << endl << "Score Board explanation\n\n"
                            "Upper Section\n";
    for(int i = 0; i < 20; i++) {
	cout << SCORE_NAME[i] << SCORE_INFO[i] << endl;
	if(i == UpperTotal)
	    cout << "\nLower Section\n";
	if(i == LowerTotal)
	    cout << endl;
    }
    cout << endl;
}

void Player::printScoreBoard() {
    cout << endl << endl << name << "'s Score Board\n\n"
                                    "Upper Section\n";
    for(int i = 0; i < 20; i++) {

	if(score[i] >= 0)
	    cout << SCORE_NAME[i] << score[i] << endl;
	else
	    cout << SCORE_NAME[i] << endl;
	if(i == UpperTotal)
	    cout << "\nLower Section\n";
	if(i == LowerTotal)
	    cout << endl;
    }
    cout << endl;
}

void Player::printDiceOnTable() {
    cout << "Dice number \t | 1 | 2 | 3 | 4 | 5 |\n"
            "            \t ---------------------\n"
            "Dice on table \t";
    int tableSize = diceOnTable.size();
    for(int i = 0; i < tableSize; i++)
	cout << " | " << diceOnTable[i];
    cout << " | " << endl;
}

void Player::keepDice() {
    cout << "Which dice would you like to keep?" << endl;
    int playerChoice;
    int tableSize = diceOnTable.size();
    while(!Tool::tryReadInt(&playerChoice) || playerChoice > tableSize || playerChoice < 0)
	cout << "That's not a valid input" << endl;

    if(playerChoice == 0)
	return;

    diceOnHand.push_back(diceOnTable[playerChoice - 1]);
    diceOnTable.erase(diceOnTable.begin() + (playerChoice - 1));
}

void Player::discardDice() {
    cout << "Which dice would you like to discard?" << endl;
    int playerChoice;
    int handSize = diceOnHand.size();
    while(!Tool::tryReadInt(&playerChoice) || playerChoice > handSize || playerChoice < 0)
	cout << "That's not a valid input" << endl;

    if(playerChoice == 0)
	return;

    diceOnTable.push_back(diceOnHand[playerChoice - 1]);
    diceOnHand.erase(diceOnHand.begin() + (playerChoice - 1));
}

void Player::rollDice() {
    turnsLeft -= 1;
    int tableSize = diceOnTable.size();
    if(tableSize == 0)
	tableSize = 5;
    diceOnTable.clear();
    cout << "Rolling dice..\n\n";
    for(int i = 0; i < tableSize; i++)
	diceOnTable.push_back(rand() % 6 + 1);
}

void Player::printPlayerHand() {
    cout << "Player's dice \t";
    int handSize = diceOnHand.size();
    for(int i = 0; i < handSize; i++)
	cout << " | " << diceOnHand[i];
    cout << " | " << endl << endl;
    cout << "Name:\t\t" << name << endl;
    cout << "Turns left:\t" << turnsLeft << endl;
    cout << "Score:\t\t" << score[GrandTotal] << endl << endl;
}

void Player::selectPlayerName() {
    cout << "Please give yourself a name: ";
    name = Tool::readLine();
    cout << endl;
}

bool Player::checkForPair() {
    int handSize = diceOnHand.size();
    for(int i = 0; i < handSize; i++)
	if(diceOnHand[i] == diceOnHand[i+1])
	    return true;
    return false;
}

int Player::checkSameFaces(int faceValue) {
    int handSize = diceOnHand.size();
    int sameFaces = 0;
    for(int i = 0; i < handSize; i++)
	if(diceOnHand[i] == faceValue)
	    sameFaces++;
    return faceValue * sameFaces;
}
