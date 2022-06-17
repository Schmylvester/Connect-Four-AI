#pragma once
#include <iostream>
#include <random>
#include <Windows.h>
#include <time.h>

#include "Constants.h"

enum GameResult
{
	NotEnded,
	RedWins,
	YellowWins,
	Draw,
};

class Connect4 {
public:
	Connect4();
	~Connect4();

	GameResult gameEnded();
	void renderBoard();
	bool takeTurn(int position);
	void resetGame();

	int getActivePlayer() { return activePlayer; }
	char** getBoard() { return board; }

private:
	GameResult checkWinner();
	void checkBoardFull();

	void printHorizontalLine();
	void declareActivePlayerWinner();
	bool dropPiece(int position);
	void switchPlayer();
	int xToYForSEWin(int x);

	GameResult result = GameResult::NotEnded;
	int lastDrop[2] = { 0, 0 };
	char symbols[2] = { 'R', 'Y' };
	int startingPlayer = 0;
	int activePlayer;
	char** board;
};