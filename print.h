#ifndef PRINT_H
#define PRINT_H

#include "player.h"

const std::string SCORE_NAME[] = {
	"[1] Ones \t\t",
	"[2] Twos \t\t",
	"[3] Threes \t\t",
	"[4] Fours \t\t",
	"[5] Fives \t\t",
	"[6] Sixes \t\t",
	"[7] Total Score \t",
	"[8] Bonus \t\t",
	"[9] Upper Total \t",

	"[10] One Pair \t\t",
	"[11] Two Pairs \t\t",
	"[12] 3 of a kind \t",
	"[13] 4 of a kind \t",
	"[14] Small Straight \t",
	"[15] Large straight \t",
	"[16] Full House \t",
	"[17] Chance \t\t",
	"[18] YATZY \t\t",
	"[19] Lower Total\t",

	"[20] Grand Total \t",
};

const std::string SCORE_INFO[] = {
	"The sum of all dice showing the number 1",
	"The sum of all dice showing the number 2",
	"The sum of all dice showing the number 3",
	"The sum of all dice showing the number 4",
	"The sum of all dice showing the number 5",
	"The sum of all dice showing the number 6",
	"The sum of all above scores",
	"If total score is 63 or more you get 50 bonus points",
	"The sum of all scores in Upper Section",

	"Two dice showing the same number. Score: Sum of those two dice",
	"Two different pairs of dice. Score: Sum of dice in those two pairs",
	"Three dice showing the same number. Score: Sum of those three dice",
	"Four dice with the same number. Score: Sum of those four dice.",
	"The combination 1-2-3-4-5. Score: 15 points (sum of all the dice)",
	"The combination 2-3-4-5-6. Score: 20 points (sum of all the dice)",
	"Any set of three combined with a different pair. Score: Sum of all the dice.",
	"Any combination of dice. Score: Sum of all the dice.",
	"All five dice with the same number. Score: 50 points.",
	"The suum of all Scores in Lower Section",
	"The sum of all scores",
};

class Print {
public:
	static void intro();
	static void playerHand(Player const& player);
	static void diceOnTable(Player const& player);
	static void scoreBoard(std::vector<Player> players);
	static void scoreBoardInfo();
};

#endif // PRINT_H
