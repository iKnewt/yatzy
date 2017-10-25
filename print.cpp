#include "Print.h"
#include "Score.h"

const string SCORE_NAME[] = {
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

const string SCORE_INFO[] = {
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

void Print::scoreBoardInfo() {
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

void Print::scoreBoard(Player const& player) {
	cout << endl << endl << player.name << "'s Score Board\n\n"
									"Upper Section\n";
	for(int i = 0; i < 20; i++) {

	if(player.score[i] >= 0)
		cout << SCORE_NAME[i] << player.score[i] << endl;
	else
		cout << SCORE_NAME[i] << endl;
	if(i == UpperTotal)
		cout << "\nLower Section\n";
	if(i == LowerTotal)
		cout << endl;
	}
	cout << endl;
}

void Print::diceOnTable(Player const& player) {
	cout << "Dice number \t | 1 | 2 | 3 | 4 | 5 |\n"
			"            \t ---------------------\n"
			"Dice on table \t";
	for(int i = 0; i < 5; i++)
		if(player.dice[i].keep == false && player.dice[i].value != 0)
			cout << " | " << player.dice[i].value;
	else
			cout << " |  ";
	cout << " | " << endl;
}

void Print::playerHand(Player const& player) {
	cout << "Player's dice \t";
	for(int i = 0; i < 5; i++)
		if(player.dice[i].keep == true && player.dice[i].value != 0)
			cout << " | " << player.dice[i].value;
	else
			cout << " |  ";
	cout << " | " << endl << endl;
	cout << "Name:\t\t" << player.name << endl;
	cout << "Turns left:\t" << player.turnsLeft << endl;
	cout << "Score:\t\t" << player.score[GrandTotal] << endl << endl;
}
