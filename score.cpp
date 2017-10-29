#include "score.h"
#include "Player.h"


void Score::calculateScores() {
	value[TotalScore] = 0;
	value[UpperTotal] = 0;
	value[LowerTotal] = 0;
	value[GrandTotal] = 0;

	for(int i = Ones; i <= Sixes; i++)
	if(value[i] >= 0)
		value[TotalScore] += value[i];
	if(value[TotalScore] >= 63) {
	value[Bonus] = 50;
	value[UpperTotal] += value[Bonus];
	}
	value[UpperTotal] += value[TotalScore];

	for(int i = OnePair; i <= Yatzy; i++)
	if(value[i] >= 0)
		value[LowerTotal] += value[i];
	value[GrandTotal] = value[UpperTotal] + value[LowerTotal];
}

void Score::sortHand(Player* player) {
	diceForScore.clear();
	for(int i = 0; i < 5; i++)
	if(player->dice[i].keep == true)
		diceForScore.push_back(player->dice[i].value);
	sort(diceForScore.begin(), diceForScore.end()); // sorts the dice on hand after value to easily compare the dice
}

int Score::checkForYatzy() {
	int handSize = diceForScore.size();
	int four = checkForFourOfAKind();
	if(handSize == 1)
	if(four > 0 && diceForScore[0] == four / 4)
		return 50;
	return 0;
}

int Score::checkForChance() {
	int handSize = diceForScore.size();
	int result = 0;
	for(int i = 0; i < handSize; i++)
	result += diceForScore[i];
	return result;
}

int Score::checkForThreeOfAKind() {
	int handSize = diceForScore.size();
	for(int i = 0; i < handSize; i++)
	if(diceForScore[i] == diceForScore[i + 1] && diceForScore[i + 1] == diceForScore[i + 2]) {
		int result = diceForScore[i] + diceForScore[i + 1] + diceForScore[i + 2];
		diceForScore.erase(diceForScore.begin() + i, diceForScore.begin() + (i + 2));
		return result;
	}
	return 0;
}

int Score::checkForFourOfAKind() {
	int three = checkForThreeOfAKind();
	int handSize = diceForScore.size();
	for(int i = 0; i < handSize; i++)
	if(diceForScore[i] == three / 3) {
		int result = diceForScore[i] + three;
		diceForScore.erase(diceForScore.begin() + i);
		return result;
	}
	return 0;
}

int Score::checkForSmallStraight() {
	bool straight = false;
	int handSize = diceForScore.size();
	if(handSize == 5)
	for(int i = 0; i < 5; i++)
		if(diceForScore[i] == i + 1)
		straight = true;
		else
		straight = false;
	if(straight)
	return 15;
	return 0;
}

int Score::checkForLargeStraight() {
	bool straight = false;
	int handSize = diceForScore.size();
	if(handSize == 5)
	for(int i = 0; i < 5; i++)
		if(diceForScore[i] == i + 2)
		straight = true;
		else
		straight = false;
	if(straight)
	return 20;
	return 0;
}

int Score::checkForFullHouse() {
	int three = checkForThreeOfAKind();
	int two = checkForPair();
	if(three != 0 && two != 0)
	return three + two;
	return 0;
}

int Score::checkForTwoPair() {
	int firstPair = checkForPair();
	int secondPair = checkForPair();
	if(firstPair != 0 && secondPair != 0)
	return firstPair + secondPair;
	return 0;
}

int Score::checkForPair() {
	int handSize = diceForScore.size();
	for(int i = 0; i < handSize; i++)
	if(diceForScore[i] == diceForScore[i + 1]) {
		int result = diceForScore[i] + diceForScore[i + 1];
		diceForScore.erase(diceForScore.begin() + i, diceForScore.begin() + (i + 1));
		return result;
	}
	return 0;
}

int Score::checkSameFaces(int faceValue) {
	int handSize = diceForScore.size();
	int sameFaces = 0;
	for(int i = 0; i < handSize; i++)
	if(diceForScore[i] == faceValue)
		sameFaces++;
	return faceValue * sameFaces;
}
