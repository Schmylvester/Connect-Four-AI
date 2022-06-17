#include "Connect4.h"

Connect4::Connect4()
{
	activePlayer = startingPlayer;
	board = new char* [BOARD_WIDTH];
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		board[x] = new char[BOARD_HEIGHT];
		for (int y = 0; y < BOARD_HEIGHT; ++y)
		{
			board[x][y] = ' ';
		}
	}
}

Connect4::~Connect4()
{
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		delete[] board[x];
	}
	delete[] board;
}

void Connect4::resetGame()
{
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		for (int y = 0; y < BOARD_HEIGHT; ++y)
		{
			board[x][y] = ' ';
		}
	}
	result = GameResult::NotEnded;
	startingPlayer = 1 - startingPlayer;
	activePlayer = startingPlayer;
}

void Connect4::printHorizontalLine()
{
	printf("\n-");
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		printf("----");
	}
	printf("\n");
}

void Connect4::renderBoard()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("\n");
	printHorizontalLine();
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		printf("|");
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			char token = board[x][BOARD_HEIGHT - 1 - y];
			int colour = token == 'R' ? 76 : token == 'Y' ? 110 : 15;
			SetConsoleTextAttribute(hConsole, colour);
			printf(" %c ", token);
			SetConsoleTextAttribute(hConsole, 15);
			printf("|");
		}
		printHorizontalLine();
	}
}

bool Connect4::takeTurn(int position)
{
	bool success = dropPiece(position);
	if (success)
	{
		checkWinner();
		checkBoardFull();
		switchPlayer();
		return true;
	}
	return false;
}

void Connect4::declareActivePlayerWinner()
{
	result = activePlayer == 0 ? GameResult::RedWins : GameResult::YellowWins;
}

int Connect4::xToYForSEWin(int x)
{
	return lastDrop[1] + (lastDrop[0] - x);
}

GameResult Connect4::checkWinner()
{
	// get min and max positions we need to check based on the last drop
	int minX = max(0, lastDrop[0] - (WIN_GOAL - 1));
	int maxX = min(BOARD_WIDTH - 1, lastDrop[0] + (WIN_GOAL - 1));
	int minY = max(0, lastDrop[1] - (WIN_GOAL - 1));
	int maxY = min(BOARD_HEIGHT - 1, lastDrop[1] + (WIN_GOAL - 1));
	// to count consecutive tiles in a given direction
	int SECount = 0;
	int NECount = 0;
	int horiCount = 0;
	int vertCount = 0;

	for (int x = minX; x <= maxX; ++x)
	{
		// count tiles going bottom left to top right
		if (x >= minY && x <= maxY)
		{
			if (board[x][x] == symbols[activePlayer])
				++NECount;
			else
				NECount = 0;
		}
		// count tiles going top left to bottom right
		int y = xToYForSEWin(x);
		if (y >= minY && y <= maxY)
		{
			if (board[x][y] == symbols[activePlayer])
				++SECount;
			else
				SECount = 0;
		}
		// count tiles going left to right
		if (board[x][lastDrop[1]] == symbols[activePlayer])
			++horiCount;
		else
			horiCount = 0;
		if (SECount >= WIN_GOAL || NECount >= WIN_GOAL || horiCount >= WIN_GOAL)
			declareActivePlayerWinner();
	}
	// count tiles going bottom to top
	for (int y = minY; y <= maxY; ++y)
	{
		if (board[lastDrop[0]][y] == symbols[activePlayer])
		{
			if (++vertCount >= WIN_GOAL)
			{
				declareActivePlayerWinner();
			}
		}
		else
		{
			vertCount = 0;
		}
	}
	return GameResult::NotEnded;
}

void Connect4::checkBoardFull()
{
	for (int x = 0; x < BOARD_WIDTH; ++x)
	{
		if (board[x][BOARD_HEIGHT - 1] == ' ')
		{
			return;
		}
	}
	result == GameResult::Draw;
}

GameResult Connect4::gameEnded()
{
	return result;
}

bool Connect4::dropPiece(int position)
{
	int y = 0;
	while (board[position][y] != ' ')
	{
		++y;
		if (y > BOARD_HEIGHT)
		{
			return false;
		}
	}
	board[position][y] = symbols[activePlayer];
	lastDrop[0] = position;
	lastDrop[1] = y;
	return true;
}

void Connect4::switchPlayer()
{
	activePlayer = 1 - activePlayer;
}