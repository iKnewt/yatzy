#include "score.h"
#include "Player.h"

// sort of messy but tried keeping it undestandable with emus
// calculates all the total scores in the game
void Score::calculateScores() {
	value[TotalScore] = 0;
	value[UpperTotal] = 0;
	value[LowerTotal] = 0;
	value[GrandTotal] = 0;
	value[Bonus] = 0;

	for (int i = Ones; i <= Sixes; i++)
		if (value[i] >= 0)
			value[TotalScore] += value[i];

	if (value[TotalScore] >= 63) {
		value[Bonus] = 50;
		value[UpperTotal] += value[Bonus];
	}
	value[UpperTotal] += value[TotalScore];

	for (int i = OnePair; i <= Yatzy; i++)
		if (value[i] >= 0)
			value[LowerTotal] += value[i];

	value[GrandTotal] = value[UpperTotal] + value[LowerTotal];
}

// adds the dice to keep in a new vector
// sorts that vector after value to make it easier to calculate scores
void Score::sortHand(Player* player) {
	diceForScore.clear();
	for (int i = 0; i < 5; i++)
		if (player->dice[i].keep == true)
			diceForScore.push_back(player->dice[i].value);
	sort(diceForScore.begin(), diceForScore.end());
}

// adds value of all dice together
int Score::chance() {
	int result = 0;
	for (size_t i = 0; i < diceForScore.size(); i++)
		result += diceForScore[i];
	return result;
}

// checks for x of a kind and returns the total of those dice, or 50 in case of yatzy
// first parameter is to indicate how many of a kind you want to check for (likely 2, 3, 4, 5)
// second parameter is to avoid having two equal pairs (eg. 4of a kind cannot count as 2 pairs)
int Score::ofAKind(int xOfaKind, int valueToAvoid) {
	int faceCheck = 0;
	int sameFaces = 1;
	for (int face : diceForScore) {
		if (face == faceCheck)
			sameFaces++;
		else
			sameFaces = 1;
		faceCheck = face;
		if (sameFaces == 5 && xOfaKind == 5)
			return 50;
		else if (sameFaces == xOfaKind && face != valueToAvoid)
			return face * xOfaKind;
	}
	return 0;
}

// uses the parameter to know what number to start counting from, then checks
// for either 1,2,3,4,5 or 2,3,4,5,6 and returns the appropriate score
int Score::straight(int firstDiceValue) {
	if (diceForScore.size() != 5)
		return 0;

	for (int i = 0; i < 5; i++)
		if (diceForScore[i] != i + firstDiceValue)
			return 0;
	return (firstDiceValue == 1) ? 15 : 20;
}

// checks for a  pair then a second pair that does not have the same faces
int Score::twoPair() {
	int firstPair = ofAKind(2,0);
	int secondPair = ofAKind(2, (firstPair / 2));
	if (firstPair != 0 && secondPair != 0)
		return firstPair + secondPair;
	else
		return 0;
}

// checks for three of a kind, then for a pair that does not have the same faces
int Score::fullHouse() {
	int three = ofAKind(3,0);
	int two = ofAKind(2, (three / 3));
	if (three != 0 && two != 0)
		return three + two;
	else
		return 0;
}

// checks how many of the dice have the same value as the parameter
int Score::sameFaces(int faceValue) {
	int sameFaces = 0;
	for (int score : diceForScore)
		if (score == faceValue)
			sameFaces++;
	return faceValue * sameFaces;
}
