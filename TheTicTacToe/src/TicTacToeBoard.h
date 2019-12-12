#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>

#define Log(x) std::cout << (x) << std::endl

class TicTacToeBoard {
private:
	inline static int MovesMade = 0;
	int counter;
	std::vector<std::vector<char>> Board1;

public:
	TicTacToeBoard();

	void PrintBoard(const TicTacToeBoard& B1) const;

	friend std::ostream& operator<<(std::ostream& out, const TicTacToeBoard& B1);

	int getMoves() const;

	void setMoves();

	bool setBoard(TicTacToeBoard& B1, const int& who, int& x, int& y);

	bool checkBoardForResult(const TicTacToeBoard& B1) const;


	std::pair<int, int> specialCheckForAIComputer(const TicTacToeBoard& B1, const int& who);

	~TicTacToeBoard();
};