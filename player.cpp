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
	Total,

	OnePair,
	TwoPairs,
	ThreeOfAKind,
	FourOfAKind,
	SmallStraight,
	LargeStraight,
	FullHouse,
	Chance,
	Yatzy,
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
	"[9] Total \t\t",		//8

	"[10] One Pair \t\t",	//9
	"[11] Two Pairs \t\t",	//10
	"[12] 3 of a kind \t",	//11
	"[13] 4 of a kind \t",	//12
	"[14] Small Straight \t",//13
	"[15] Large straight \t",//14
	"[16] Full House \t",	//15
	"[17] Chance \t\t",		//16
	"[18] YATZY \t\t",	//17
	"[19] Grand Total \t",	//18
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
	"Of Upper Selection",

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
};

void Player::playerTurn(){

	calculateScores();
	printPlayerHand();

	cout << "[1] Roll\n"
			"[2] Save hand to Score\n"
			"[3] Print Scoreboard\n"
			"[4] Print explanation for scoreboard\n";
	int playerChoice;
	while(!Tool::tryReadInt(&playerChoice) || playerChoice > 5 || playerChoice < 1)
		cout << "That's not a valid input";

	switch (playerChoice) {
		case 1:
			rollDice();
			break;
		case 2:
			saveToScore();
			break;
		case 3:
			printScoreBoard();
			break;
		case 4:
			printScoreBoardInfo();
			break;
		default:
			break;
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

	switch (userInput-1) {
		case Ones:
			scores[Ones] = checkSameFaces(1);
			break;
		case Twos:
		        scores[Twos] = checkSameFaces(2);
			break;
		case Threes:
		        scores[Threes] = checkSameFaces(3);
			break;
		case Fours:
		        scores[Fours] = checkSameFaces(4);
			break;
		case Fives:
		        scores[Fives] = checkSameFaces(5);
			break;
		case Sixes:
		        scores[Sixes] = checkSameFaces(6);
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
		case Total:
		case GrandTotal:
			cout << "You can't change this value\n";
			break;
		default:
			break;
	}
	diceOnHand.clear();
	diceOnTable.resize(5);
}

void Player::calculateScores() {
	scores[TotalScore] = 0;
	scores[Total] = 0;
	scores[GrandTotal] = 0;

	for(int i = Ones; i <= Sixes; i++)
		scores[TotalScore] += scores[i];
	if(scores[TotalScore] >= 63)
		scores[Bonus] = 50;
	scores[Total] = scores[TotalScore] + scores[Bonus];

	for(int i = OnePair; i <= Yatzy; i++)
		scores[GrandTotal] += scores[i];
	scores[GrandTotal] += scores[Total];

}

void Player::sortHand() {
	sort(diceOnHand.begin(), diceOnHand.end());
}

void Player::printScoreBoardInfo() {
	cout << endl << endl << "Score Board explanation\n\n"
							"Upper Section\n";
	for(int i = 0; i < 19; i++) {
		cout << SCORE_NAME[i] << SCORE_INFO[i] << endl;
		if(i == 8)
			cout << "\nLower Section\n";
	}
	cout << endl;
}


void Player::printScoreBoard() {
	cout << endl << endl << name << "'s Score Board\n\n"
									"Upper Section\n";
	for(int i = 0; i < 19; i++) {
		cout << SCORE_NAME[i] << scores[i] << endl;
		if(i == 8)
			cout << "\nLower Section\n";
	}
	cout << endl;
}

//void Player::printRolledDice() {
//	for(int i = 0; i < numberOfDice; i++)
//		cout << "Die[" << i + 1 << "] = " << diceOnTable[i] << endl;
//	cout << endl;
//}
void Player::printRolledDice() {
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
	while(!Tool::tryReadInt(&playerChoice) || playerChoice > numberOfDice || playerChoice < 0)
		cout << "That's not a valid input" << endl;

	if(playerChoice == 0)
		return;

	diceOnHand.push_back(diceOnTable[playerChoice - 1]);
	diceOnTable.erase(diceOnTable.begin() + (playerChoice - 1));
	numberOfDice -= 1;
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
	numberOfDice += 1;
}

void Player::rollDice() {
        int tableSize = diceOnTable.size();
	diceOnTable.clear();
	cout << "Rolling dice..\n\n";
	for(int i = 0; i < tableSize; i++)
		diceOnTable.push_back(rand() % 6 + 1);


	bool cont = true;
	while(cont) {
		printRolledDice();
		printPlayerHand();
		cout << "What would you like to do?\n"
				"[1] Roll again\n"
				"[2] Keep one dice\n"
				"[3] Discard one of your dice\n"
				"[4] Continue game\n";
		int playerChoice;
		while(!Tool::tryReadInt(&playerChoice))
			cout << "Invalid input\n";

		switch (playerChoice) {
			case 1:
				rollDice();
				break;
			case 2:
				keepDice();
				break;
			case 3:
				discardDice();
				break;
			case 4:
				cont = false;
				break;
			default:
				break;
		}
	}
}

void Player::printPlayerHand() {
	cout << name << "'s dice \t";
	numberOfDiceOnHand = diceOnHand.size();
	for(int i = 0; i < numberOfDiceOnHand; i++)
		cout << " | " << diceOnHand[i];
	cout << " | " << endl << endl;
}

void Player::selectPlayerName() {
	cout << "Please give yourself a name: ";
	name = Tool::readLine();
	cout << endl;
}

bool Player::checkForPair() {
	numberOfDiceOnHand = diceOnHand.size();
	for(int i = 0; i < numberOfDiceOnHand; i++)
	        if(diceOnHand[i] == diceOnHand[i+1])
			return true;
	return false;
}

int Player::checkSameFaces(int faceValue) {
	numberOfDiceOnHand = diceOnHand.size();
	int sameFaces = 0;
	for(int i = 0; i < numberOfDiceOnHand; i++)
		if(diceOnHand[i] == faceValue)
			sameFaces++;
	return faceValue * sameFaces;
}
