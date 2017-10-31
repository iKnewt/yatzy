#include "score.h"
#include "Player.h"

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

void Score::sortHand(Player* player) {
	diceForScore.clear();
	for (int i = 0; i < 5; i++)
		if (player->dice[i].keep == true)
			diceForScore.push_back(player->dice[i].value);
	sort(diceForScore.begin(), diceForScore.end());
}

int Score::chance() {
	int result = 0;
	for (size_t i = 0; i < diceForScore.size(); i++)
		result += diceForScore[i];
	return result;
}

// breaks if you have 2x2 alike and look for 3 alike, fix this later
int Score::ofAKind(int xOfaKind) {
	int scoreCheck = 0;
	int sameFaces = 1;
	for (int score : diceForScore) {
		if (score == scoreCheck)
			sameFaces++;
		scoreCheck = score;
		if (sameFaces == 5)
			return 50;
		else if (sameFaces == xOfaKind)
			return score * xOfaKind;
	}
	return 0;
}

int Score::differentPair(int valueToAvoid) {
	int scoreCheck = 0;
	int sameFaces = 1;
	for (int score : diceForScore) {
		if (score == scoreCheck)
			sameFaces++;
		scoreCheck = score;
		if (sameFaces == 2 && score != valueToAvoid)
			return score * 2;
		else
			sameFaces = 1;
	}
	return 0;
}

int Score::straight() {
	if (diceForScore.size() != 5)
		return 0;

	int firstDiceValue = diceForScore[0];
	for (int i = 0; i < 5; i++)
		if (diceForScore[i] != i + firstDiceValue)
			return 0;
	return (firstDiceValue == 1) ? 15 : 20;
}

int Score::twoPair() {
	int firstPair = ofAKind(2);
	int secondPair = differentPair(firstPair / 2);
	if (firstPair != 0 && secondPair != 0)
		return firstPair + secondPair;
	else
		return 0;
}

int Score::fullHouse() {
	int three = ofAKind(3);
	int two = differentPair(three / 3);
	if (three != 0 && two != 0)
		return three + two;
	else
		return 0;
}

int Score::sameFaces(int faceValue) {
	int sameFaces = 0;
	for (int score : diceForScore)
		if (score == faceValue)
			sameFaces++;
	return faceValue * sameFaces;
}
