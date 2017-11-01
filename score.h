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
	int twoPair();
	int ofAKind(int howManyOfaKind, int valueToAvoid);
	int sameFaces(int faceValue);
	int yatzy();
	int chance();
	int straight(int firstDiceValue);
	int fullHouse();
};

#endif // SCORE_H
