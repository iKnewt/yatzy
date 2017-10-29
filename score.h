#ifndef SCORE_H
#define SCORE_H

#include <vector>

class Player;

enum ScoreEnum {
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

class Score {

public:
	std::vector<int> diceForScore = {0,0,0,0,0};
	int value[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	void sortHand(Player* player);
	void calculateScores();
	int checkForPair();
	int checkForTwoPair();
	int checkSameFaces(int faceValue);
	int checkForYatzy();
	int checkForChance();
	int checkForThreeOfAKind();
	int checkForFourOfAKind();
	int checkForSmallStraight();
	int checkForLargeStraight();
	int checkForFullHouse();
};

#endif // SCORE_H
