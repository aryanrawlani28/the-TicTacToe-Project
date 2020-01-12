#include "TicTacToeBoard.h"

TicTacToeBoard::TicTacToeBoard()
{
	Board1 = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};
}

const void TicTacToeBoard::getTitle()
{
	std::cout << mainTitle;
}

void TicTacToeBoard::PrintBoard(const TicTacToeBoard& B1) const {
	std::cout << B1;
}

int TicTacToeBoard::getMoves() const
{
		return this->MovesMade;
}

void TicTacToeBoard::setMoves() {
	this->MovesMade = ++MovesMade;
}

bool TicTacToeBoard::setBoard(TicTacToeBoard& B1, const int& who, int& x, int& y) {

	if (who % 2 == 0 || who == 0) {
		B1.Board1[x][y] = 'X';		//The player who wins the toss, gets the first chance and the letter "X" to play. In increments of 2, his chance comes again.
	}
	else {
		B1.Board1[x][y] = 'O';
	}

	if (who > 3) {								//Minimum 4 moves for a winner. No need to check board for winner before that.
		if (checkBoardForResult(B1)) {
			return true;	//if this returns true, our game comes to know that game should be stopped, because we have a winner.
		}
		else {
			return false;	//else it continues as normal.
		}
	}

	return false;
}

bool TicTacToeBoard::checkBoardForResult(const TicTacToeBoard& B1) const {	//Checks board if someone has won. If yes, returns true. Otherwise, false.

	char board[] = { 'X', 'O' };

	for (char c : board) {
		if (c == B1.Board1[0][0]) {		//Primary diagonal
			if (c == B1.Board1[1][1]) {
				if (c == B1.Board1[2][2]) {
					return true;
				}
			}

		}

		if (c == B1.Board1[2][0]) {		//Secondary diagonal
			if (c == B1.Board1[1][1]) {
				if (c == B1.Board1[0][2]) {
					return true;
				}
			}

		}

		if (c == B1.Board1[0][0]) {			// Row0
			if (c == B1.Board1[0][1]) {
				if (c == B1.Board1[0][2]) {
					return true;
				}
			}
		}

		if (c == B1.Board1[1][0]) {			// Row1
			if (c == B1.Board1[1][1]) {
				if (c == B1.Board1[1][2]) {
					return true;
				}
			}
		}

		if (c == B1.Board1[2][0]) {			// Row2
			if (c == B1.Board1[2][1]) {
				if (c == B1.Board1[2][2]) {
					return true;
				}
			}
		}

		if (c == B1.Board1[0][0]) {			// Col0
			if (c == B1.Board1[1][0]) {
				if (c == B1.Board1[2][0]) {
					return true;
				}
			}
		}

		if (c == B1.Board1[0][1]) {			// Col1
			if (c == B1.Board1[1][1]) {
				if (c == B1.Board1[2][1]) {
					return true;
				}
			}
		}

		if (c == B1.Board1[0][2]) {			// Col2
			if (c == B1.Board1[1][2]) {
				if (c == B1.Board1[2][2]) {
					return true;
				}
			}
		}
	}

	return false;
}

std::pair<int, int> TicTacToeBoard::specialCheckForAIComputer(const TicTacToeBoard& B1, const int& who) {
	this->counter = 0;
	char ch;

	//This function checks if the computer can win, or the player can win. If yes, return that pair. Else, return a pair(-1,-1) for further analysis.

	if (who == 0 || who % 2 == 0) {		// Decide who we are actually checking.
		ch = 'X';
	}
	else {
		ch = 'O';
	}


	//	Primary Diagonal
	if (ch == B1.Board1[0][0]) {
		counter++;
	}
	if (ch == B1.Board1[1][1]) {
		counter++;
	}
	if (ch == B1.Board1[2][2]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[0][0] && ch == B1.Board1[1][1] && ' ' == B1.Board1[2][2]) {
			return std::make_pair(2, 2);
		}
		else if (ch == B1.Board1[1][1] && ch == B1.Board1[2][2] && ' ' == B1.Board1[0][0]) {
			return std::make_pair(0, 0);
		}
		else if (ch == B1.Board1[0][0] && ch == B1.Board1[2][2] && ' ' == B1.Board1[1][1]) {
			return std::make_pair(1, 1);
		}

	}

	counter = 0;

	//	Secondary diagonal
	if (ch == B1.Board1[2][0]) {
		counter++;
	}
	if (ch == B1.Board1[1][1]) {
		counter++;
	}
	if (ch == B1.Board1[0][2]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[2][0] && ch == B1.Board1[1][1] && ' ' == B1.Board1[0][2]) {
			return std::make_pair(0, 2);
		}
		else if (ch == B1.Board1[1][1] && ch == B1.Board1[0][2] && ' ' == B1.Board1[2][0]) {
			return std::make_pair(2, 0);
		}
		else if (ch == B1.Board1[0][2] && ch == B1.Board1[2][0] && ' ' == B1.Board1[1][1]) {
			return std::make_pair(1, 1);
		}
	}
	counter = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////

	if (ch == B1.Board1[0][0]) {		//Row 0
		counter++;
	}
	if (ch == B1.Board1[0][1]) {
		counter++;
	}
	if (ch == B1.Board1[0][2]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[0][0] && ch == B1.Board1[0][1] && ' ' == B1.Board1[0][2]) {
			return std::make_pair(0, 2);
		}
		else if (ch == B1.Board1[0][1] && ch == B1.Board1[0][2] && ' ' == B1.Board1[0][0]) {
			return std::make_pair(0, 0);
		}
		else if (ch == B1.Board1[0][2] && ch == B1.Board1[0][0] && ' ' == B1.Board1[0][1]) {
			return std::make_pair(0, 1);
		}
	}

	counter = 0;

	if (ch == B1.Board1[1][0]) {		//Row 1
		counter++;
	}
	if (ch == B1.Board1[1][1]) {
		counter++;
	}
	if (ch == B1.Board1[1][2]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[1][0] && ch == B1.Board1[1][1] && ' ' == B1.Board1[1][2]) {
			return std::make_pair(1, 2);
		}
		else if (ch == B1.Board1[1][1] && ch == B1.Board1[1][2] && ' ' == B1.Board1[1][0]) {
			return std::make_pair(1, 0);
		}
		else if (ch == B1.Board1[1][2] && ch == B1.Board1[1][0] && ' ' == B1.Board1[1][1]) {
			return std::make_pair(1, 1);
		}
	}
	counter = 0;

	if (ch == B1.Board1[2][0]) {		//Row 2
		counter++;
	}
	if (ch == B1.Board1[2][1]) {
		counter++;
	}
	if (ch == B1.Board1[2][2]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[2][0] && ch == B1.Board1[2][1] && ' ' == B1.Board1[2][2]) {
			return std::make_pair(2, 2);
		}
		else if (ch == B1.Board1[2][1] && ch == B1.Board1[2][2] && ' ' == B1.Board1[2][0]) {
			return std::make_pair(2, 0);
		}
		else if (ch == B1.Board1[2][2] && ch == B1.Board1[2][0] && ' ' == B1.Board1[2][1]) {
			return std::make_pair(2, 1);
		}
	}
	counter = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////

	if (ch == B1.Board1[0][0]) {		//Col 0
		counter++;
	}
	if (ch == B1.Board1[1][0]) {
		counter++;
	}
	if (ch == B1.Board1[2][0]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[0][0] && ch == B1.Board1[1][0] && ' ' == B1.Board1[2][0]) {
			return std::make_pair(2, 0);
		}
		else if (ch == B1.Board1[1][0] && ch == B1.Board1[2][0] && ' ' == B1.Board1[0][0]) {
			return std::make_pair(0, 0);
		}
		else if (ch == B1.Board1[2][0] && ch == B1.Board1[0][0] && ' ' == B1.Board1[1][0]) {
			return std::make_pair(1, 0);
		}
	}
	counter = 0;

	if (ch == B1.Board1[0][1]) {		//Col 1
		counter++;
	}
	if (ch == B1.Board1[1][1]) {
		counter++;
	}
	if (ch == B1.Board1[2][1]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[0][1] && ch == B1.Board1[1][1] && ' ' == B1.Board1[2][1]) {
			return std::make_pair(2, 1);
		}
		else if (ch == B1.Board1[1][1] && ch == B1.Board1[2][1] && ' ' == B1.Board1[0][1]) {
			return std::make_pair(0, 1);
		}
		else if (ch == B1.Board1[2][1] && ch == B1.Board1[0][1] && ' ' == B1.Board1[1][1]) {
			return std::make_pair(1, 1);
		}
	}
	counter = 0;

	if (ch == B1.Board1[0][2]) {		//Col 2
		counter++;
	}
	if (ch == B1.Board1[1][2]) {
		counter++;
	}
	if (ch == B1.Board1[2][2]) {
		counter++;
	}

	if (counter == 2) {
		if (ch == B1.Board1[0][2] && ch == B1.Board1[1][2] && ' ' == B1.Board1[2][2]) {
			return std::make_pair(2, 2);
		}
		else if (ch == B1.Board1[1][2] && ch == B1.Board1[2][2] && ' ' == B1.Board1[0][2]) {
			return std::make_pair(0, 2);
		}
		else if (ch == B1.Board1[2][2] && ch == B1.Board1[0][2] && ' ' == B1.Board1[1][2]) {
			return std::make_pair(1, 2);
		}
	}

	return std::make_pair(-1, -1);
}

TicTacToeBoard::~TicTacToeBoard() {
	Log("\n\nLooks like the game is over.");

	Log("Quitting the game in 5 seconds... say goodbye to the board....\n");

	std::cout << "===========================================================" << std::endl;

	std::cout << std::flush;
	std::cin.clear();
	this->MovesMade = 0;
	std::this_thread::sleep_for(std::chrono::seconds(3));
}
