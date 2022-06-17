#pragma once
#include <random>

#include "Constants.h"

class Player
{
public:
	Player() = default;
	Player(char symbol);
	~Player() = default;
	int makeChoice(char** board);
	std::vector<float>* getWeights() { return &weights; }

private:
	int getWeightForTwoNodes(int inNode, int outNode, int inNodesSize, int layer);
	std::vector<float> hiddenNodes;
	std::vector<float> outputNodes;
	char mySymbol;
	int hiddenCount = 20;

	std::vector<float> weights;
};