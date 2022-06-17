#include "Player.h"

Player::Player(char symbol)
{
	mySymbol = symbol;
	int inputCount = BOARD_WIDTH * BOARD_HEIGHT;
	int outputCount = BOARD_WIDTH;

	hiddenNodes.assign(hiddenCount, 0);
	outputNodes.assign(outputCount, 0);

	for (int i = 0; i < inputCount * hiddenCount + outputCount * hiddenCount; ++i)
	{
		weights.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (rand() % 2 == 0 ? -1 : 1));
	}
}

int Player::getWeightForTwoNodes(int inNode, int outNode, int inNodesSize, int layer)
{
	return inNode + (outNode * inNodesSize) + (layer * hiddenCount * BOARD_WIDTH * BOARD_HEIGHT);
}

int Player::makeChoice(char** board)
{
	std::fill(hiddenNodes.begin(), hiddenNodes.end(), 0);
	std::fill(outputNodes.begin(), outputNodes.end(), 0);
	for (int x = 0, i = 0; x < BOARD_WIDTH; ++x)
	{
		for (int y = 0; y < BOARD_HEIGHT; ++y, ++i)
		{
			int inputValue = 0;
			if (board[x][y] != ' ')
			{
				inputValue = board[x][y] == mySymbol ? 1 : -1;
			}
			for (int h = 0; h < hiddenCount; ++h)
			{
				hiddenNodes[h] += inputValue * weights[getWeightForTwoNodes(i, h, BOARD_WIDTH * BOARD_HEIGHT, 0)];
			}
		}
	}
	for (int h = 0; h < hiddenCount; ++h)
	{
		hiddenNodes[h] /= BOARD_WIDTH * BOARD_HEIGHT;
		for (int o = 0; o < BOARD_WIDTH; ++o)
		{
			outputNodes[o] += hiddenNodes[h] * weights[getWeightForTwoNodes(h, o, hiddenCount, 1)];
		}
	}

	int bestIndex = 0;
	float best = outputNodes[0] / hiddenCount;
	for (int o = 0; o < BOARD_WIDTH; ++o)
	{
		if (board[o][BOARD_HEIGHT - 1] == ' ')
		{
			float val = outputNodes[o] / hiddenCount;
			if (val > best)
			{
				bestIndex = o;
				best = val;
			}
		}
	}


	return bestIndex;
}