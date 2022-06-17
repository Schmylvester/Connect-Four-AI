#include <random>

#include "Connect4.h"
#include "Player.h"

int main()
{
	srand(time(0));
	Player players[2] =
	{
		Player('R'),
		Player('Y')
	};
	for (int i = 0; i < 5; ++i)
	{
		Connect4 connect4;
		GameResult result = GameResult::NotEnded;
		while (result == GameResult::NotEnded)
		{
			int activePlayer = connect4.getActivePlayer();
			int position = players[activePlayer].makeChoice(connect4.getBoard());
			connect4.takeTurn(position);
			result = connect4.gameEnded();
		}
		connect4.renderBoard();
		switch (result)
		{
		case RedWins:
			printf("Red wins!");
			break;
		case YellowWins:
			printf("Yellow wins!");
			break;
		case Draw:
			printf("It's a draw.");
			break;
		default:
			printf("You're a bad programmer.");
			break;
		}
		connect4.resetGame();
	}

	return 0;
}